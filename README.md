# FlexTyper

[![CircleCI](https://circleci.com/gh/wassermanlab/OpenFlexTyper.svg?style=svg)](https://circleci.com/gh/wassermanlab/OpenFlexTyper) [![Documentation Status](https://readthedocs.org/projects/openflextyper/badge/?version=latest)](https://openflextyper.readthedocs.io/en/latest/?badge=latest)
[![GitHub release](https://img.shields.io/github/release/wassermanlab/openflextyper/all?logo=GitHub)](https://github.com/wassermanlab/openflextyper/releases/latest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


## Overview

> FlexTyper is a tool which enables the creation of an FM-index of raw, next generation sequencing data to enable rapid and flexible sequence queries.

We demonstrate the utility of these flexible queries performed as kmer (sequence substrings of length 'k') searches for two applications including SNP genotyping from whole genome sequencing, and viral detection from RNA-seq. 

To learn more about FlexTyper, see our preprint on bioRxiv:

[Demonstrating the utility of flexible sequence queries against indexed short reads with FlexTyper](https://www.biorxiv.org/content/10.1101/2020.03.02.973750v1)



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


## Demo

![](docs/FlexTyper_test.gif)


## Contributers

[<img alt="tixii" src="https://avatars2.githubusercontent.com/u/7527871?s=460&v=4" width="117">](https://github.com/tixii/) |
[<img alt="Phil" src="https://avatars1.githubusercontent.com/u/16579982?s=460&v=4" width="117">](https://github.com/Phillip-a-richmond) |
[<img alt="kounkou" src="https://avatars0.githubusercontent.com/u/2589171?s=460&v=4" width="117">](https://github.com/kounkou) |
[<img alt="tamario" src="https://avatars2.githubusercontent.com/u/15660317?s=460&v=4" width="117">](https://github.com/tamario) |
:---: | :---: | :---: | :---: | 
[Alice Kaye](https://github.com/tixii) | [Phillip Richmond](https://github.com/Phillip-a-richmond) | [Jacques Kounkou](https://github.com/kounkou) | [Tamar Av-Shalom](https://github.com/tamario)


## Full Documentation

For more information about FlexTyper, please refer to our online documentation on [readthedocs](https://flextyper.readthedocs.io/en/latest/)


## License

The MIT License (MIT)

Copyright (c) 2019, Wasserman lab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
