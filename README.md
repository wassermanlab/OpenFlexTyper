# FlexTyper

[![CircleCI](https://circleci.com/gh/wassermanlab/OpenFlexTyper.svg?style=svg)](https://circleci.com/gh/wassermanlab/OpenFlexTyper)

> An FM-index based tool for rapid searching of interesting variants/sequences within unmapped short read sequences

Contributers:

[<img alt="kounkou" src="https://avatars2.githubusercontent.com/u/7527871?s=460&v=4" width="117">](https://github.com/tixii/) |
[<img alt="kounkou" src="https://avatars1.githubusercontent.com/u/16579982?s=460&v=4" width="117">](https://github.com/Phillip-a-richmond) |
[<img alt="kounkou" src="https://avatars0.githubusercontent.com/u/2589171?s=460&v=4" width="117">](https://github.com/kounkou) |
[<img alt="kounkou" src="https://avatars2.githubusercontent.com/u/15660317?s=460&v=4" width="117">](https://github.com/tamario) |
:---: | :---: | :---: | :---: | 
[Alice Kaye](https://github.com/tixii) | [Phillip Richmond](https://github.com/Phillip-a-richmond) | [Jacques KOUNKOU](https://github.com/kounkou) | [Tamar AvShalom](https://github.com/tamario)


## Overview

![](docs/images/FmTyper_Overview.png)


## Quick start installation

This is an example of installing FlexTyper using the install script. It assumes Git is already installed.

```bash
git clone https://github.com/wassermanlab/OpenFlexTyper.git
cd OpenFlexTyper
./install.sh
```

Accept the packages installation, as a result, flextyper is located inside the build directory.


## A little paragraph

The purpose of FlexTyper is to rapidly query an unmapped read file (fastq) for variants/kmers of interest. The core of FlexTyper relies on the FM-index of the raw reads, developed by Alice Kaye. This indexed read set is designed for rapid queries of kmers, sequence substrings of length ‘k’, against an entire set of unmapped reads. With this ability to rapidly scan for substrings against an unmapped read set, we can perform meaningful queries for a variety of applications including genotyping for presence of pathogenic variants, coverage analysis for known probes contained within the CytoscanHD chromosomal microarray set, and ancestry/ethnicity inference from population discriminating polymorphisms. The tool is designed in a flexible manner with respect to the query capabilities, making it available for extension to other organisms, genome versions, and applications. We anticipate that FlexTyper’s utility will grow as datasets cataloguing variants of interest continue to expand.

