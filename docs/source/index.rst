.. OpenFlexTyper documentation master file, created by
   sphinx-quickstart on Tue Oct 22 14:56:10 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to OpenFlexTyper's documentation!
=========================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


FlexTyper
=========

Requirements
^^^^^^^^^^^^

FlexTyper requires :

-  A modern, C++17 ready compiler such as gcc 7.4.0 or higher.
-  Qt version 5.11.0
-  A 64-bit operating system. Currently, Linux supported
-  For increased performance on large number of queries, we recommand
   using a SSC-like machine

Build from source
^^^^^^^^^^^^^^^^^

To Download and install FlexTyper, use the following commands :

.. code:: bash

   git clone https://github.com/wassermanlab/FlexTyper.git
   cd FMTyper/
   mkdir build
   cd build
   qmake ..
   make

or just

.. code:: bash

   git clone https://github.com/wassermanlab/FlexTyper.git
   cd FlexTyper/
   sudo bash install.sh

Getting Started
^^^^^^^^^^^^^^^

To get you started with FlexTyper, you can start by creating a
Setting.ini file. Setting.ini files look like the following, and are a
convenient resource file used when running FlexTyper.

`Example of FlexTyper Setting file`_

As you can see, the configuration contains all information needed to run
a search.

Execution
^^^^^^^^^

FlexTyper provides 2 main features :

-  searching, used to search for kmers inside an FmIndex
-  indexing, used to creates an FmIndex from a FASTA file

.. code:: bash

   ./flextyper

   Usage
    flextyper [feature] [options...]

    Features :
       searching   uses the FmIndex to search
       indexing    uses a fasta file to produce the FmIndex

    Options  :
       -h, --help  displays this help

    Example :
    flextyper searching -h

Example of searching execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To use FlexTyper in searching mode, you need you need to create a
configuration file containing details about the search you want to do. A
template for the configuration file can be found here `Example of
FlexTyper Setting file`_ To launch the search, please type de following
command :

.. code:: bash

   flextyper searching -c Setting.ini

Help can be displayed typing :

.. code:: bash

   flextyper searching -h

or

.. code:: bash

   flextyper searching --help

Example of searching indexing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To use FlexTyper in indexing mode, you need you need to provide a FASTA
file.

.. code:: bash

   flextyper indexing -f input.fasta -o . -x input.fm9

Help can be displayed typing :

.. code:: bash

   flextyper indexing -h

or

.. code:: bash

   flextyper indexing --help

Bug Reporting
^^^^^^^^^^^^^

While you’re using FlexTyper, you might still discover issues. Please
feel free to report any problems you may experience. We thank you in
advance for your contributions. To report, please provide a screenshot
and a set of logs compressed, and open an issue on github.

Contribute
^^^^^^^^^^

Please contact Project Owners for contributions.

.. _Example of FlexTyper Setting file: ../extras/Setting.ini
