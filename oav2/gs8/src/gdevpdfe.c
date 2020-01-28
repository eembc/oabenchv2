/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gdevpdfe.c 6655 2006-03-13 20:53:43Z stefan $ */
/* Metadata writer. */
#include "gx.h"
#include "string_.h"
#include "time_.h"
#include "stream.h"
#include "gp.h"
#include "smd5.h"
#include "gscdefs.h"
#include "gdevpdfx.h"
#include "gdevpdfg.h"
#include "gdevpdfo.h"
#include "gdevpdtf.h"

/* Write XML data */
private void
pdf_xml_data_write(stream *s, const byte *data, int data_length)
{
    int l = data_length;
    const byte *p = data;

    for (; l--; p++) {
	switch (*p) {
	    case '<' : stream_puts(s, "&lt;"); break;
	    case '>' : stream_puts(s, "&gt;"); break;
	    case '&' : stream_puts(s, "&amp;"); break;
	    case '\'': stream_puts(s, "&apos;"); break;
	    case '"' : stream_puts(s, "&quot;"); break;
	    default:
		if (*p < 32 || *p > 127)
		    pprintd1(s, "&#%d;", *p);
		else
		    stream_putc(s, *p);
	}
    }
}

/* Write XML string */
private inline void
pdf_xml_string_write(stream *s, const char *data)
{
    pdf_xml_data_write(s, (const byte *)data, strlen(data));
}

/* Begin an opening XML tag */
private inline void
pdf_xml_tag_open_beg(stream *s, const char *data)
{
    stream_putc(s, '<');
    stream_puts(s, data);
}

/* End an XML tag */
private inline void
pdf_xml_tag_end(stream *s)
{
    stream_putc(s, '>');
}

/* End an empty XML tag */
private inline void
pdf_xml_tag_end_empty(stream *s)
{
    stream_puts(s, "/>");
}

/* Write an opening XML tag */
private inline void
pdf_xml_tag_open(stream *s, const char *data)
{
    stream_putc(s, '<');
    stream_puts(s, data);
    stream_putc(s, '>');
}

/* Write a closing XML tag */
private inline void
pdf_xml_tag_close(stream *s, const char *data)
{
    stream_puts(s, "</");
    stream_puts(s, data);
    stream_putc(s, '>');
}

/* Write an attribute name */
private inline void
pdf_xml_attribute_name(stream *s, const char *data)
{
    stream_putc(s, ' ');
    stream_puts(s, data);
    stream_putc(s, '=');
}

/* Write a attribute value */
private inline void
pdf_xml_attribute_value(stream *s, const char *data)
{
    stream_putc(s, '\'');
    pdf_xml_string_write(s, data);
    stream_putc(s, '\'');
}
/* Write a attribute value */
private inline void
pdf_xml_attribute_value_data(stream *s, const byte *data, int data_length)
{
    stream_putc(s, '\'');
    pdf_xml_data_write(s, data, data_length);
    stream_putc(s, '\'');
}

/* Begin an  XML instruction */
private inline void
pdf_xml_ins_beg(stream *s, const char *data)
{
    stream_puts(s, "<?");
    stream_puts(s, data);
}

/* End an XML instruction */
private inline void
pdf_xml_ins_end(stream *s)
{
    stream_puts(s, "?>");
}

/* Write a newline character */
private inline void
pdf_xml_newline(stream *s)
{
    stream_puts(s, "\n");
}

/* Copy to XML output */
private inline void
pdf_xml_copy(stream *s, const char *data)
{
    stream_puts(s, data);
}


/* --------------------------------------------  */

private void
pdf_xmp_time(char *buf, int buf_length)
{
    /* We don't write a day time because we don't have a time zone. */
    struct tm tms;
    time_t t;
    char buf1[4+1+2+1+2+1]; /* yyyy-mm-dd\0 */

    time(&t);
    tms = *localtime(&t);
    sprintf(buf1,
	    "%04d-%02d-%02d",
	    tms.tm_year + 1900, tms.tm_mon + 1, tms.tm_mday);
    strncpy(buf, buf1, buf_length);
}

private void
pdf_xmp_write_docinfo_item(gx_device_pdf *pdev, stream *s, const char *key, const char *default_value,
			   void(*write)(stream *s, const byte *data, int data_length))
{
    const cos_value_t *v = cos_dict_find(pdev->Info, (const byte *)key, strlen(key));

    if (v != NULL && (v->value_type == COS_VALUE_SCALAR || 
			v->value_type == COS_VALUE_CONST)) {
	if (v->contents.chars.size > 2 && v->contents.chars.data[0] == '(')
	    write(s, v->contents.chars.data + 1, v->contents.chars.size - 2);
	else
	    write(s, v->contents.chars.data, v->contents.chars.size);
    } else 
	stream_puts(s, default_value);
}

private uint64_t
pdf_uuid_time(gx_device_pdf *pdev)
{   
    long *dt = pdev->uuid_time; /* In seconds since Jan. 1, 1980 and fraction in nanoseconds. */
    uint64_t t;

    /* UUIDs use time in 100ns ticks since Oct 15, 1582. */
    t = (uint64_t)10000000 * dt[0] + dt[0] / 100; /* since Jan. 1, 1980 */
    t += (uint64_t) (1000*1000*10)         /* seconds */
       * (uint64_t) (60 * 60 * 24)         /* days */
       * (uint64_t) (17+30+31+365*397+99); /* # of days */
    return t;
}

private void writehex(char **p, ulong v, int l)
{
    int i = l * 2;
    static const char digit[] = "0123456789abcdef";

    for (; i--;)
	*((*p)++) = digit[v >> (i * 4) & 15];
}

private void
pdf_make_uuid(const byte node[6], uint64_t uuid_time, ulong time_seq, char *buf, int buf_length)
{   
    char b[40], *p = b;
    ulong  uuid_time_lo = (ulong)(uuid_time & 0xFFFFFFFF);       /* MSVC 7.1.3088           */
    ushort uuid_time_md = (ushort)((uuid_time >> 32) & 0xFFFF);  /* cannot compile this     */
    ushort uuid_time_hi = (ushort)((uuid_time >> 48) & 0x0FFF);  /* as function arguments.  */

    writehex(&p, uuid_time_lo, 4); /* time_low */
    *(p++) = '-';
    writehex(&p, uuid_time_md, 2); /* time_mid */
    *(p++) = '-';
    writehex(&p, uuid_time_hi | (ushort)(1 << 12), 2); /* time_hi_and_version */
    *(p++) = '-';
    writehex(&p, (time_seq & 0x3F00) >> 8, 1); /* clock_seq_hi_and_reserved */
    writehex(&p, time_seq & 0xFF, 1); /* clock_seq & 0xFF */
    *(p++) = '-';
    writehex(&p, node[0], 1);
    writehex(&p, node[1], 1);
    writehex(&p, node[2], 1);
    writehex(&p, node[3], 1);
    writehex(&p, node[4], 1);
    writehex(&p, node[5], 1);
    *p = 0;
    strncpy(buf, b, buf_length);
}

private int
pdf_make_instance_uuid(gx_device_pdf *pdev, const byte digest[6], char *buf, int buf_length)
{
    if (pdev->InstanceUUID.size) {
	int l = min(buf_length - 1, pdev->InstanceUUID.size);

	memcpy(buf, pdev->InstanceUUID.data, l);
	buf[l] = 0;
    } else
	pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, buf, buf_length);
    return 0;
}

private int
pdf_make_document_uuid(gx_device_pdf *pdev, const byte digest[6], char *buf, int buf_length)
{
    if (pdev->DocumentUUID.size) {
	int l = min(buf_length - 1, pdev->DocumentUUID.size);

	memcpy(buf, pdev->DocumentUUID.data, l);
	buf[l] = 0;
    } else
	pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, buf, buf_length);
    return 0;
}

private char dd[]={'\'', 0xEF, 0xBB, 0xBF, '\'', 0};

/* --------------------------------------------  */

/* Write Document metadata */
private int
pdf_write_document_metadata(gx_device_pdf *pdev, const byte digest[6])
{
    char instance_uuid[40], document_uuid[40], date_time[40];
    int code;
    stream *s = pdev->strm;

    code = pdf_make_instance_uuid(pdev, digest, instance_uuid, sizeof(instance_uuid));
    if (code < 0)
	return code;
    code = pdf_make_document_uuid(pdev, digest, document_uuid, sizeof(document_uuid));
    if (code < 0)
	return code;
    pdf_xmp_time(date_time, sizeof(date_time));
    pdf_xml_ins_beg(s, "xpacket");
    pdf_xml_attribute_name(s, "begin");
    pdf_xml_copy(s, dd);
    pdf_xml_attribute_name(s, "id");
    pdf_xml_attribute_value(s, "W5M0MpCehiHzreSzNTczkc9d");
    pdf_xml_ins_end(s);
    pdf_xml_newline(s);

    pdf_xml_copy(s, "<?adobe-xap-filters esc=\"CRLF\"?>\n");
    pdf_xml_copy(s, "<x:xmpmeta xmlns:x='adobe:ns:meta/'"
	                      " x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'>\n");
    {
	pdf_xml_copy(s, "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
	                         "xmlns:iX='http://ns.adobe.com/iX/1.0/'>\n");
	{

    	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:pdf");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/pdf/1.3/");
	    pdf_xml_attribute_name(s, "pdf:Producer");
	    pdf_xmp_write_docinfo_item(pdev, s,  "/Producer", "UnknownProduicer",
			pdf_xml_attribute_value_data);
	    pdf_xml_tag_end_empty(s);
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xap");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/");
	    pdf_xml_attribute_name(s, "xap:ModifyDate");
	    pdf_xml_attribute_value(s, date_time);
	    pdf_xml_attribute_name(s, "xap:CreateDate");
	    pdf_xml_attribute_value(s, date_time);
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open_beg(s, "xap:CreatorTool");
		pdf_xml_tag_end(s);
		{
		    char buf[10];

		    sprintf(buf, "%d.%02d", (int)(gs_revision / 100), (int)(gs_revision % 100));
		    pdf_xml_string_write(s, gs_product);
		    pdf_xml_string_write(s, " ");
		    pdf_xml_string_write(s, buf);
		    pdf_xml_string_write(s, " PDF Writer");
		}
		pdf_xml_tag_close(s, "xap:CreatorTool");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xapMM");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/mm/");
	    pdf_xml_attribute_name(s, "xapMM:DocumentID");
	    pdf_xml_attribute_value(s, document_uuid);
	    pdf_xml_tag_end_empty(s);
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:dc");
	    pdf_xml_attribute_value(s, "http://purl.org/dc/elements/1.1/");
	    pdf_xml_attribute_name(s, "dc:format");
	    pdf_xml_attribute_value(s,"application/pdf");
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open(s, "dc:title");
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xmp_write_docinfo_item(pdev, s,  "/Title", "Untitled", 
				    pdf_xml_data_write);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "dc:title");

		if (cos_dict_find(pdev->Info, (const byte *)"/Author", 7)) {
		    pdf_xml_tag_open(s, "dc:creator");
		    {   /* According to the PDF/A specification
			   "it shall be represented by an ordered Text array of
			   length one whose single entry shall consist 
			   of one or more names". */
			pdf_xml_tag_open(s, "rdf:Seq");
			{
			    pdf_xml_tag_open(s, "rdf:li");
			    {
    				pdf_xmp_write_docinfo_item(pdev, s,  "/Author", "Unknown", 
					    pdf_xml_data_write);
			    }
			    pdf_xml_tag_close(s, "rdf:li");
			}
			pdf_xml_tag_close(s, "rdf:Seq");
		    }
		    pdf_xml_tag_close(s, "dc:creator");
		}
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);
	}
	pdf_xml_copy(s, "</rdf:RDF>\n");
    }
    pdf_xml_copy(s, "</x:xmpmeta>\n");

    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "<?xpacket end='w'?>");
    return 0;
}

int
pdf_document_metadata(gx_device_pdf *pdev)
{   
    if (pdev->CompatibilityLevel < 1.4)
	return 0;
    if (pdev->ParseDSCCommentsForDocInfo || pdev->PreserveEPSInfo) {
	pdf_resource_t *pres;
	char buf[20];
	byte digest[6];
	int code;
	int options = DATA_STREAM_NOT_BINARY;

	sflush(pdev->strm);
	s_MD5C_get_digest(pdev->strm, digest, sizeof(digest));
	if (pdev->EncryptMetadata)
	    options |= DATA_STREAM_ENCRYPT;
	code = pdf_open_aside(pdev, resourceOther, gs_no_id, &pres, true, options);
	if (code < 0)
	    return code;
	code = pdf_write_document_metadata(pdev, digest);
	if (code < 0)
	    return code;
	code = pdf_close_aside(pdev);
	if (code < 0)
	    return code;
	code = COS_WRITE_OBJECT(pres->object, pdev);
	if (code < 0)
	    return code;
	sprintf(buf, "%ld 0 R", pres->object->id);
	cos_dict_put_c_key_object(pdev->Catalog, "/Metadata", pres->object);
    }
    return 0;
}

/* --------------------------------------------  */

/* Write Font metadata */
private int
pdf_write_font_metadata(gx_device_pdf *pdev, const pdf_base_font_t *pbfont, 
			const byte *digest, int digest_length)
{
    char instance_uuid[40];
    int code;
    stream *s = pdev->strm;
    gs_font_info_t info;
    gs_font_base *pfont = pbfont->complete;

    if (pfont == NULL)
	pfont = pbfont->copied;
    /* Fixme: For True Type fonts need to get Coipyright, Owner from the TT data. */
    pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, instance_uuid, sizeof(instance_uuid));
    code = pfont->procs.font_info((gs_font *)pfont, NULL,
		    (FONT_INFO_COPYRIGHT | FONT_INFO_NOTICE |
			FONT_INFO_FAMILY_NAME | FONT_INFO_FULL_NAME),
					&info);
    if (code < 0)
	return code;
    pdf_xml_ins_beg(s, "xpacket");
    pdf_xml_attribute_name(s, "begin");
    pdf_xml_copy(s, dd);
    pdf_xml_attribute_name(s, "id");
    pdf_xml_attribute_value(s, "W5M0MpCehiHzreSzNTczkc9d");
    pdf_xml_ins_end(s);
    pdf_xml_newline(s);

    pdf_xml_copy(s, "<?adobe-xap-filters esc=\"CRLF\"?>\n");
    pdf_xml_copy(s, "<x:xmpmeta xmlns:x='adobe:ns:meta/'"
	                      " x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'>\n");
    {
	pdf_xml_copy(s, "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
	                         "xmlns:iX='http://ns.adobe.com/iX/1.0/'>\n");
	{

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xmp");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/");
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open_beg(s, "xmp:Title");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, pbfont->font_name.data, pbfont->font_name.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmp:Title");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);


	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xmpRights");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/rights/");
	    pdf_xml_tag_end(s);
	    if (info.members & FONT_INFO_COPYRIGHT) {
		pdf_xml_tag_open_beg(s, "xmpRights:Copyright");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Copyright.data, info.Copyright.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:Copyright");

		/* Don't have an Owner, write Copyright instead. */
		pdf_xml_tag_open_beg(s, "xmpRights:Owner");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Copyright.data, info.Copyright.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:Owner");
	    }
	    {
		pdf_xml_tag_open_beg(s, "xmpRights:Marked");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_string_write(s, "True");
		}
		pdf_xml_tag_close(s, "xmpRights:Marked");
	    }
	    if (info.members & FONT_INFO_NOTICE) {
		pdf_xml_tag_open_beg(s, "xmpRights:UsageTerms");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Notice.data, info.Notice.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:UsageTerms");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);
	}
	pdf_xml_copy(s, "</rdf:RDF>\n");
    }
    pdf_xml_copy(s, "</x:xmpmeta>\n");

    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "<?xpacket end='w'?>");
    return 0;
}

int
pdf_font_metadata(gx_device_pdf *pdev, const pdf_base_font_t *pbfont, 
		  const byte *digest, int digest_length, gs_id *metadata_object_id)
{  
    *metadata_object_id = gs_no_id;
    if (pdev->CompatibilityLevel < 1.4)
	return 0;
    /* The PDF/A specification redss about 
	"embedded Type 0, Type 1, or TrueType font programs",
	but we believe that "embedded Type 0 font programs"
	do not exist.
	We create Metadata for Type 1,2,42,9,11.
    */
    if (pdev->PDFA) {
	pdf_resource_t *pres;
	byte digest[6];
	int code;
	int options = DATA_STREAM_NOT_BINARY;

	sflush(pdev->strm);
	s_MD5C_get_digest(pdev->strm, digest, sizeof(digest));
	if (pdev->EncryptMetadata)
	    options |= DATA_STREAM_ENCRYPT;
	code = pdf_open_aside(pdev, resourceOther, gs_no_id, &pres, true, options);
	if (code < 0)
	    return code;
	code = pdf_write_font_metadata(pdev, pbfont, digest, digest_length);
	if (code < 0)
	    return code;
	code = pdf_close_aside(pdev);
	if (code < 0)
	    return code;
	code = COS_WRITE_OBJECT(pres->object, pdev);
	if (code < 0)
	    return code;
	*metadata_object_id = pres->object->id;
    }
    return 0;
}
