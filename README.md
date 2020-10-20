# FlexTyper
![Generate Documentation](https://github.com/wassermanlab/OpenFlexTyper/workflows/Generate%20Documentation/badge.svg?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


## Overview

> FlexTyper is a tool which enables the creation of an FM-index of raw, next generation sequencing data to enable rapid and flexible sequence queries.

We demonstrate the utility of these flexible queries performed as kmer (sequence substrings of length 'k') searches for two applications including SNP genotyping from whole genome sequencing, and viral detection from RNA-seq. 

To learn more about FlexTyper, see our preprint on bioRxiv:

[Demonstrating the utility of flexible sequence queries against indexed short reads with FlexTyper](https://www.biorxiv.org/content/10.1101/2020.03.02.973750v1)


## Full Documentation

For more information about FlexTyper, please refer to [GitHubPages](https://wassermanlab.github.io/OpenFlexTyper/)

## Quick start installation

OpenFlexTyper is installed with the install.sh script provided in the repository. Installation is currently supported for Linux operating systems. 
 
The installation assumes that you have **git** installed.

Open a terminal and enter :

```bash
git clone https://github.com/wassermanlab/OpenFlexTyper.git
cd OpenFlexTyper
bash install.sh
```

## Example

This repository comes with an example to test-run your installation and familiarize yourself with the usage of FlexTyper. 

You can learn more about examples [here](https://github.com/wassermanlab/OpenFlexTyper/tree/master/examples)

## Customizing Query Files

To design query files, follow the instructions in the fmformatter directory [here](https://github.com/wassermanlab/OpenFlexTyper/tree/master/fmformatter)

## Downstream Processing

The output files from FlexTyper can be formatted into commonly used formats, e.g. VCF format with a basic genotyping methods.

To learn more, see the fmformatter directory [here](https://github.com/wassermanlab/OpenFlexTyper/tree/master/fmformatter)

## Contributers
[Alice Kaye](https://github.com/tixii) | [Phillip Richmond](https://github.com/Phillip-a-richmond) | [Jacques Kounkou](https://github.com/kounkou) | [Tamar Av-Shalom](https://github.com/tamario)


## License

The MIT License (MIT)

Copyright (c) 2020, Wasserman lab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
