\page search 

# How to search with FlexTyper 

## Cmd Line: 
You can display the input options using 

~~~~~~~~~~~~~~~~~~~~~{.html}
Usage: ../build/flextyper [options] outputFile
Description: flextyper enables the user to quickly search for kmers inside the FmIndex

Options:
  -h, --help              Displays this help.
  -v, --verbose           prints debugging messages
  -c, --config <file>     ini file to use
  -k, --kmerSize <value>  kmer size
  -s, --stride <value>    stride
  -m, --maxOcc <value>    maxOcc
  -u, --unique            ignore nonunique kmers

Arguments:
  outputFile              fm9 dataset
~~~~~~~~~~~~~~~~~~~~~

## Setting.ini 

The settings file contains all the parameters for the search. 

\subpage settingini "Setting Ini File"

## Example 1: Viral Detection 

\subpage viralsearchexample 

## Example 2: SNV Detection

\subpage snvsearchexample