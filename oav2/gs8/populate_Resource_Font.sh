#!/bin/sh
if [ $# -lt 1 ] ; then
    echo
    echo usage: populate_Resource_Font.sh path_to_urwfonts
    echo
    exit 1
fi
mkdir Resource/Font
cp $1/b018015l.pfb Resource/Font/URWBookmanL-DemiBold
cp $1/b018035l.pfb Resource/Font/URWBookmanL-DemiBoldItal
cp $1/b018012l.pfb Resource/Font/URWBookmanL-Ligh
cp $1/b018032l.pfb Resource/Font/URWBookmanL-LighItal
cp $1/n022003l.pfb Resource/Font/NimbusMonL-Regu
cp $1/n022023l.pfb Resource/Font/NimbusMonL-ReguObli
cp $1/n022004l.pfb Resource/Font/NimbusMonL-Bold
cp $1/n022024l.pfb Resource/Font/NimbusMonL-BoldObli
cp $1/a010013l.pfb Resource/Font/URWGothicL-Book
cp $1/a010033l.pfb Resource/Font/URWGothicL-BookObli
cp $1/a010015l.pfb Resource/Font/URWGothicL-Demi
cp $1/a010035l.pfb Resource/Font/URWGothicL-DemiObli
cp $1/n019003l.pfb Resource/Font/NimbusSanL-Regu
cp $1/n019023l.pfb Resource/Font/NimbusSanL-ReguItal
cp $1/n019004l.pfb Resource/Font/NimbusSanL-Bold
cp $1/n019024l.pfb Resource/Font/NimbusSanL-BoldItal
cp $1/n019043l.pfb Resource/Font/NimbusSanL-ReguCond
cp $1/n019063l.pfb Resource/Font/NimbusSanL-ReguCondItal
cp $1/n019044l.pfb Resource/Font/NimbusSanL-BoldCond
cp $1/n019064l.pfb Resource/Font/NimbusSanL-BoldCondItal
cp $1/p052003l.pfb Resource/Font/URWPalladioL-Roma
cp $1/p052023l.pfb Resource/Font/URWPalladioL-Ital
cp $1/p052004l.pfb Resource/Font/URWPalladioL-Bold
cp $1/p052024l.pfb Resource/Font/URWPalladioL-BoldItal
cp $1/c059013l.pfb Resource/Font/CenturySchL-Roma
cp $1/c059033l.pfb Resource/Font/CenturySchL-Ital
cp $1/c059016l.pfb Resource/Font/CenturySchL-Bold
cp $1/c059036l.pfb Resource/Font/CenturySchL-BoldItal
cp $1/n021003l.pfb Resource/Font/NimbusRomNo9L-Regu
cp $1/n021023l.pfb Resource/Font/NimbusRomNo9L-ReguItal
cp $1/n021004l.pfb Resource/Font/NimbusRomNo9L-Medi
cp $1/n021024l.pfb Resource/Font/NimbusRomNo9L-MediItal
cp $1/s050000l.pfb Resource/Font/StandardSymL
cp $1/z003034l.pfb Resource/Font/URWChanceryL-MediItal
cp $1/d050000l.pfb Resource/Font/Dingbats
