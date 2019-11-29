*****************
OpenFlexTyper
*****************

The purpose of FlexTyper is to rapidly query an unmapped read file (fastq) for variants/kmers of interest.
The core of FlexTyper relies on the FM-index of the raw reads, developed by Alice Kaye. 
This indexed read set is designed for rapid queries of kmers, sequence substrings of length ‘k’, against an entire set of unmapped reads. 
With this ability to rapidly scan for substrings against an unmapped read set, we can perform meaningful queries 
for a variety of applications including genotyping for presence of pathogenic variants, coverage analysis for known probes 
contained within the CytoscanHD chromosomal microarray set, and ancestry/ethnicity inference from population discriminating polymorphisms. 
The tool is designed in a flexible manner with respect to the query capabilities, making it available for extension to other organisms, 
genome versions, and applications. We anticipate that FlexTyper’s utility will grow as datasets cataloguing 
variants of interest continue to expand.

.. toctree::
   :maxdepth: 2

   requirements

.. toctree::
   :maxdepth: 2

   quick_start_installation
 
.. toctree::
   :maxdepth: 2

   getting_started      

.. toctree::
   :maxdepth: 2

   code_source_documentation      


Indices and tables
==================

* :ref:`genindex`
* :ref:`search`
