# FlexTyper

#### Requirements

FlexTyper requires :

*	A modern, C++17 ready compiler such as gcc 7.4.0 or higher.
*	Qt version 5.11.0
*	A 64-bit operating system. Currently, Linux supported
*	For increased performance on large number of queries, we recommand using a SSC-like machine

#### Build from source

To Download and install FlexTyper, use the following commands :

```bash
git clone https://github.com/wassermanlab/FlexTyper.git
cd FMTyper/
mkdir build
cd build
qmake ..
make
```

or just

```bash
git clone https://github.com/wassermanlab/FlexTyper.git
cd FlexTyper/
sudo bash install.sh
```

#### Getting Started

To get you started with FlexTyper, you can start by creating a Setting.ini file.
Setting.ini files look like the following, and are a convenient resource file used
when running FlexTyper.

[Example of FlexTyper Setting file](../extras/Setting.ini)

As you can see, the configuration contains all information needed to run a search.

#### Example of execution

Launching a search is very easy, just call FlexTyper with the configuration file that your populated.

```bash
./FlexTyper ftsearch_config -c Settings.ini
```

#### Benchmarks

To ensure the FlexTyper application runs efficiently on your system, we suggest you to run the Benchmark
test. The Benchmark test the application against a set of Perfect FmIndex reads.
After running the Benchmark, you can compare the results and check that, in monothreaded search, the results
match the following results :

[Example of FlexTyper result file](../extras/Benchmark.tsv)

#### Bug Reporting

While you're using FlexTyper, you might still discover issues. Please feel free to report any problems you
may experience. We thank you in advance for your contributions.
To report, please provide a screenshot and a set of logs compressed, and open an issue on github.

#### Contribute

Please contact Project Owners for contributions.
