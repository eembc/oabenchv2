# Introduction

OABench 2.0 is a second-generation suite of benchmarks that allows the user to approximate the performance of processors in printers, plotters, and other office automation systems that handle text and image processing tasks. Compared to OABench 1.1, it includes new Ghostscript and Bezier benchmarks as well as new datasets and self-checking features. Even if you’re not working on a printer or image processing application, the demanding workload provided by OABench 2.0 will stress processors at all levels.

Its five benchmark kernels include the following:

## Bezier

Benchmarks the classic Bezier curve algorithm by interpolating a set of points defined by the four points of a Bezier curve.

## Dithering

The benchmark uses the Floyd-Steinberg error diffusion dithering algorithm.

## Ghostscript

Provides an indication of the potential performance of an embedded processor running a PostScript printer engine. OABench 2.0 can be run with or without this benchmark.

## Image Rotation

The benchmark uses a bitmap rotation algorithm to perform a clockwise 90° rotation on a binary image.

## Text Parsing

The benchmark parses Boolean expressions made up of text strings and tests bit manipulation, comparison, and indirect reference capabilities to test the potential performance of a printer interpretive control language.

# Score

A complete OABench Version 2.0 score report consists of 87 separate benchmark scores in five overall categories: Bezier, Dither, Rotate, Text, and Ghostscript. Several consolidated scores are also reported. Results for Bezier, Dither, Rotate, and Text are combined into a single-number OAV2mark consolidated score, while the Ghostscript results are combined into a series of nine consolidated scores, as shown in the table below. Scores are calculated by taking the geometric mean of the kernels in each group.

To calculate a geometric mean, multiply all the results of the tests together and take the nth root of the product, where n equals the number of tests.

# Notes

This repository contains the OABench benchmark and its corresponding Test Harness for the Version 2.0 benchmarks produced by EEMBC between 2004 and 2007. This benchmark is released as-is, meaning EEMBC will follow issues but cannot guarantee support. Issues should be considered errata, and changes to the benchmark core algorithms are no longer considered compatible with version 2.0.

In order to save disk space, all of the 600 dpi Ghostscript datasets have been gzipped. Before building and running, you must `gunzip` all of the files in `oav2/gs-output-dpi-600`.

