#---------------------------------------------------
# Phillip Richmond
# This script is for plotting data for FastTyper
# 2019-07-03
# 
# CHANGES HISTORY
# Godfrain Jacques Kounkou      used params instead of hard coded paths     2019 Sept 23
# Phil Richmond + Tamar Av Shalom    Fixed the 0-0 error in the delta plots    2019 Sept 25
# 	Removed dir, added usage saying show full filepath, output plots will go to a new directory
#	  made by a system call for mkdir -p output/. 
#   Fixed ouput --> output in DeltaRefPositional plot
#   FUTURE improvement: Added argparser for easier usage
# Phil Richmond
# Adding plotting from performance
#---------------------------------------------------


# Install if needed
install.packages("tidyverse")
#install.packages("grid")
#install.packages("cowplot")
install.packages("ggsci")
#install.packages("ggplot2")
#install.packages("argparser")
library(ggsci)
#library(cowplot)
library(tidyverse)
#library(grid)
library(dplyr)
library(argparser)

# Functional command argument from the command line. 
# Commented out here as argparser gives more flexibility
#args = commandArgs(trailingOnly=TRUE)
#if (length(args) != 1) {
#    stop("one argument must be supplied")
#}

# ArgParser set up, 
# Phil finish this later
#p <- arg_parser("A plotting tool for FlexTyper")
#p <- add_argument(p, "input", help="input file")
#p <- add_argument(p, "type", help="type of file to plot, e.g. ")
#argv <- parse_args(p)
#?argparser

# - Fig 3A,B - #

# Make an output directory called output/
system('mkdir -p /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/')
system('cd /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
#dir   <- file.path("output")
# files <- c("QUERY_FILE_SProb_21-10_20190731.tsv")
#files <- args
files <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/performance/MultiKmerSearch.tsv")
 

KmerData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerData)
summarise(KmerData)
KmerData
KmerData$Threads <- as.numeric(as.character(KmerData$Threads))
KmerData$number_of_kmers <- as.numeric(as.character(KmerData$number_of_kmers))
KmerData$search_time <- as.numeric(as.character(KmerData$search_time))
KmerData$kmer_size <- as.numeric(as.character(KmerData$kmer_size))

my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
my.theme2 <- theme_classic()  + theme(aspect.ratio = 1/2) + theme(legend.position="bottom")

#PlotKmers <- function(my.theme) {}

p_line_thread1 <- ggplot(data=KmerData[KmerData$Threads==1 & KmerData$number_of_kmers>=10,],aes(x = number_of_kmers, y = search_time, group = kmer_size),na.rm=TRUE) 
p_line_thread1 + 
  my.theme2 +
  geom_path(aes(color=kmer_size)) +
  geom_point(aes(color=kmer_size)) +
  scale_x_continuous(trans='log10') +
  scale_y_continuous(trans='log10') +
  scale_color_gradient(low="blue",high="red") +
  ggsave("KmerPerformance1thread.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
  
p_line_thread2 <- ggplot(data=KmerData[KmerData$Threads==30 & KmerData$number_of_kmers>=10,],aes(x = number_of_kmers, y = search_time, group = kmer_size,linetype='dashed'),na.rm=TRUE) 
p_line_thread2 + 
  my.theme2 +
  geom_line(aes(color=kmer_size), linetype='dashed') +
  geom_point(aes(color=kmer_size), shape=2) +
  scale_x_continuous(trans='log10') +
  scale_y_continuous(trans='log10') +
  scale_color_gradient(low="blue",high="red") +
  ggsave("KmerPerformance30thread.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
  

# This doesn't work right now
p_line_thread_combined <- ggplot(data=KmerData[KmerData$number_of_kmers>=10,],aes(x = number_of_kmers, y = search_time, color=kmer_size, group=kmer_size, linetype=factor(KmerData$Threads),na.rm=TRUE)) 
p_line_thread_combined + 
  my.theme2 +
  geom_path(aes(color=kmer_size)) +
  geom_point(aes(color=kmer_size)) +
  scale_x_continuous(trans='log10') +
  scale_y_continuous(trans='log10') +
  scale_color_gradient(low="blue",high="red") +
  ggsave("KmerPerformanceBoththreads.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
  
  


# - Fig 3C - #

files <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/performance/MultiKmerSearch.tsv")


KmerThreadData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerData)
summarise(KmerData)
KmerThreadData
KmerThreadData$number_of_threads <- as.numeric(as.character(KmerData$number_of_threads))
KmerThreadData$number_of_kmers <- as.numeric(as.character(KmerData$number_of_kmers))
KmerData$search_time <- as.numeric(as.character(KmerData$search_time))
KmerData$kmer_size <- as.numeric(as.character(KmerData$kmer_size))

my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
my.theme2 <- theme_classic()  + theme(aspect.ratio = 1/2) + theme(legend.position="bottom")

#PlotKmers <- function(my.theme) {}

p_line_thread1 <- ggplot(data=KmerData[KmerData$Threads==1 & KmerData$number_of_kmers>=10,],aes(x = number_of_kmers, y = search_time, group = kmer_size),na.rm=TRUE) 
p_line_thread1 + 
  my.theme2 +
  geom_path(aes(color=kmer_size)) +
  geom_point(aes(color=kmer_size)) +
  scale_x_continuous(trans='log10') +
  scale_y_continuous(trans='log10') +
  scale_color_gradient(low="blue",high="red") +
  ggsave("KmerPerformance1thread.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")





  
  

#PlotKmers(my.theme)







# Read csv into data frame
CountData <- read.csv(file.path(files), sep='\t',header=TRUE)
dim(CountData)
summarise(CountData)

# Convert relevant text columns to ints. Note, these are hard-coded to the column headers in the output files as of 20190925
CountData$Ref_count <- as.numeric(as.character(CountData$Ref_count))
CountData$Alt_count <- as.numeric(as.character(CountData$Alt_count))
CountData$RefCoverageFromBam <- as.numeric(as.character(CountData$RefCoverageFromBam))
CountData$AltCoverageFromBam <- as.numeric(as.character(CountData$AltCoverageFromBam))
# Make another column as the sum of ref and alt from flex typer
CountData$TotalFlexTyper <- CountData$Ref_count + CountData$Alt_count 


# Make the deltas, accounting for instances where both are 0
CountData$DeltaRef <- ifelse((CountData$Ref_count == 0 & CountData$RefCoverageFromBam==0), NA, CountData$Ref_count-CountData$RefCoverageFromBam)
# Repeat for delta Alt
CountData$DeltaAlt <- ifelse((CountData$Alt_count == 0 & CountData$AltCoverageFromBam==0), NA, CountData$Alt_count-CountData$AltCoverageFromBam)
# Repeat for delta Total
CountData$DeltaTotal <- ifelse((CountData$TotalFlexTyper == 0 & CountData$TotalCoverageFromBam==0), NA, CountData$TotalFlexTyper-CountData$TotalCoverageFromBam)


# Re-sort by chromosome and then position
CountData <- CountData[order(CountData$Chrom, CountData$Pos),]


# Begin to plot, set some stuff up
my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
my.theme2 <- theme_classic()  + theme(aspect.ratio = 1/4) + theme(legend.position="bottom")
coverageBamFlexTyperRef <- function(my.theme) {
    # Make basic plot as p, comparing ref coverage from bam and ref_count from FlexTyper
    p_ref_scatter <- ggplot(data=CountData,aes(x = RefCoverageFromBam, y = Ref_count),na.rm=TRUE)
    p_ref_scatter         + 
      my.theme          + 
      xlim(1,100)       + 
      ylim(1,100)       + 
      geom_point(alpha=0.01,size=3,shape=20) + 
      geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
      xlab('Reference Coverage From Bam') +
      ylab('Reference Count From FlexTyper')
    ggsave("RefCoverageScatter.png",plot= last_plot(), path="output/")
}

coverageBamFlexTyperAlt <- function(my.theme) {
	# Repeat for alt coverage
	p_alt_scatter <- ggplot(data=CountData,aes(x = AltCoverageFromBam, y = Alt_count),na.rm=TRUE)
	p_alt_scatter     + 
	  my.theme          +
  	xlim(1,100)       + 
	  ylim(1,100)       +
	  geom_point(alpha=0.01,size=3,shape=20) +
	  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
	  xlab('Alternate Coverage From Bam') +
	  ylab('Alternate Count From FlexTyper')
	ggsave("AltCoverageScatter.png",plot= last_plot(),path="output/")
}

totalCoverageScatterBamFlexTyper <- function(my.theme) {
	# And total coverage
	p_total_scatter <- ggplot(data=CountData,aes(x = TotalCoverageFromBam, y = TotalFlexTyper),na.rm=TRUE)
	p_total_scatter   + 
	  my.theme 	  +
	  xlim(1,100) 	  + 
	  ylim(1,100) 	  +
	  geom_point(alpha=0.01,size=3,shape=20) +
	  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
	  xlab('Total Coverage From Bam') +
	  ylab('Total Count From FlexTyper')
	ggsave("TotalCoverageScatter.png",plot= last_plot(), path="output/")
}

posAlongXAxisTotalFlexTyperonY <- function(my.theme) {
	# Plot with the position along the x axis
	p_pos_both_total <- ggplot(data=CountData[CountData$Chrom=='1',], aes(x = Pos, y = TotalFlexTyper, color="FlexTyper" ))
	p_pos_both_total  +
	  my.theme 	  +
	  ylim(1,80) 	  +
	  geom_point(alpha=0.1) +
	  geom_abline(linetype=2,slope=0, intercept=50) +
	  geom_point(aes(x = Pos, y = TotalCoverageFromBam, color="BAM" ),alpha=0.1) +
	  xlab('Chromsomal Position [chromosome 1]')
	  ylab('Total Coverage and Total Count')
	ggsave("TotalPositionalBoth.png",plot= last_plot(), height=5, width=15, path="output/")
}

deltasAlongPosAxisTot <- function(my.theme) {
	# Plot the delta along the positional axis, centered on 0 for y 
	p_pos_delta_total <- ggplot(data=CountData[CountData$Chrom=='1',], aes(x=Pos, y=DeltaTotal))
	p_pos_delta_total + 
	  my.theme 	  +
	  ylim(-50,50) 	  +
	  geom_point(alpha=0.05) +
	  geom_abline(linetype=2,slope=0,intercept=0,color='black') +
	  xlab('Chromsomal Position [chromosome 1]')
	ggsave("DeltaTotalPositional.png",plot= last_plot(), height=5, width=15, path="output/")
}

deltaAlongPosAxisAlt <- function(my.theme) {
	# Plot the delta along the positional axis, centered on 0 for y 
	p_pos_delta_alt <- ggplot(data=CountData[CountData$Chrom=='1',], aes(x=Pos, y=DeltaAlt))
	p_pos_delta_alt  + 
	  my.theme 	 +
	  ylim(-50,50) 	 +
	  geom_point(alpha=0.05,color='red') +
	  geom_abline(linetype=2,slope=0,intercept=0,color='red') +
	  xlab('Chromsomal Position [chromosome 1]')
	ggsave("DeltaAltPositional.png",plot= last_plot(), height=5, width=15, path="output/")
}

deltaAlongPosAxisRef <- function(my.theme) {
	# Plot the delta along the positional axis, centered on 0 for y 
	p_pos_delta_ref <- ggplot(data=CountData[CountData$Chrom=='1',], mapping=aes(x=Pos, y=DeltaRef))
	p_pos_delta_ref  + 
	  my.theme 	 +
	  ylim(-50,50) 	 +
	  geom_point(alpha=0.05,color='blue') +
	  geom_abline(linetype=2,slope=0,intercept=0,color='red') +
	  xlab('Chromsomal Position [chromosome 1]')
	ggsave("DeltaRefPositional.png",plot= last_plot(), height=5, width=15, path="output/")
}

deltas_histogram_ref <- function(my.theme) {
	# Plot a histogram of the deltas
	p_delta_hist <- ggplot(data=CountData)
	p_delta_hist 	 +
	  my.theme 	 + 
	  xlim(-50,50) 	 +
	  geom_histogram(binwidth=2,aes(DeltaRef,color="Reference"),alpha=0.05) +
	  xlab('Delta between FlexTyper - BamCoverage')
	ggsave("DeltaHistBoth.png",plot= last_plot(), path="output/")
}

deltas_histogram_both <- function(my.theme) {
	# Plot a histogram of the deltas
	p_delta_hist <- ggplot(data=CountData)
	p_delta_hist 	 +
	  my.theme 	 + 
	  xlim(-50,50) 	 +
	  geom_histogram(binwidth=2,aes(DeltaRef,color="Reference"),alpha=0.05) +
	  geom_histogram(binwidth=2,aes(DeltaAlt,color="Alternate"),alpha=0.05) +
	  xlab('Delta between FlexTyper - BamCoverage')
	ggsave("DeltaHistBoth.png",plot= last_plot(), path="output/")
}




# __main__ calls
coverageBamFlexTyperRef(my.theme)
coverageBamFlexTyperAlt(my.theme)
totalCoverageScatterBamFlexTyper(my.theme)
posAlongXAxisTotalFlexTyperonY(my.theme2)
deltasAlongPosAxisTot(my.theme2)
deltaAlongPosAxisRef(my.theme2)
deltas_histogram_ref(my.theme)
deltas_histogram_both(my.theme)
deltaAlongPosAxisAlt(my.theme2)
