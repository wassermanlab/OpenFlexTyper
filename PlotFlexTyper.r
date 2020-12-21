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
#library(argparser)
library(pheatmap)
library(ggplot2)
#install.packages("umap")
library(umap)



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

# - Fig 3A - #

# Make an output directory called output/
system('mkdir -p /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/')
system('cd /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
setwd('/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
#dir   <- file.path("output")
# files <- c("QUERY_FILE_SProb_21-10_20190731.tsv")
#files <- args
files <- c("./performance/MultiKmerSearch.tsv")


KmerData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerData)
summarise(KmerData)
KmerData
KmerData$Threads <- (as.character(KmerData$Threads))
KmerData$number_of_kmers <- as.numeric(as.character(KmerData$number_of_kmers))
KmerData$search_time <- as.numeric(as.character(KmerData$search_time))
KmerData$kmer_size <- (as.character(KmerData$kmer_size))

my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
my.theme2 <-  theme_classic() + theme(aspect.ratio = 1/2) + theme(legend.position="bottom")

#PlotKmers <- function(my.theme) {}
subDF <- subset(KmerData,kmer_size %in% c("25","150") & number_of_kmers > 10)
subDFgrouped <- group_by(subDF,Threads)
subDFgrouped
p_line_thread1 <- ggplot(data=subDFgrouped, aes(x = number_of_kmers, y = search_time),na.rm=TRUE) 
p_line_thread1 + 
  my.theme2 +
  geom_line(aes(color=kmer_size, linetype=Threads)) +
  geom_point(aes(color=kmer_size, shape=Threads)) +
  scale_x_continuous(trans='log10') +
  scale_y_continuous(trans='log10') +
  ggsave("KmerPerformance1thread.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
  

##############
# - Fig 3B - #
##############
files <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/performance/Multithread_Sub25_Deltas.tsv")

KmerThreadData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerThreadData)
summarise(KmerThreadData)
KmerThreadData
KmerThreadData$Threads <- as.numeric(as.character(KmerThreadData$Threads))
KmerThreadData$Expected <- as.numeric(as.character(KmerThreadData$Expected))
KmerThreadData$Actual <- as.numeric(as.character(KmerThreadData$Actual))
KmerThreadData$Delta <- as.numeric(as.character(KmerThreadData$Delta))

p_line_thread_by_time <- ggplot(data=KmerThreadData,aes(x = Threads, y = Actual),na.rm=TRUE) 
p_line_thread_by_time + 
  my.theme2 +
  geom_line(color='blue', linetype='solid') +
  geom_point(color='blue', shape=19) +
  xlim(0, 32) +
  ylab('Time (s)') +
  scale_x_continuous(breaks = c(0,KmerThreadData$Threads), expand = c(0, 0)) +
  expand_limits(x = 0, y = c(0,8100)) +
  scale_y_continuous(expand = c(0, 0)) +
  coord_cartesian(clip = "off") +
  geom_errorbar(aes(ymin=Expected, ymax=Actual, color='red')) +
  geom_line(aes(x=Threads, y=Expected),linetype='dashed') +
  ggsave("KmerPerformancekmer25_10000_deltas.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")

############## 
# - Fig 3C - #
##############

system('cd /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
setwd('/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
files <- c("./performance/Performance_Fig3C.tsv")
ThreadData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerThreadData)
summarise(ThreadData)
ThreadData
ThreadData$threads <- as.numeric(as.character(ThreadData$threads))
ThreadData$time_s <- as.numeric(as.character(ThreadData$time_s))


p_line_thread_by_time <- ggplot(data=ThreadData,aes(x = threads, y = time_s),na.rm=TRUE) 
p_line_thread_by_time + 
  my.theme2 +
  geom_line(color='blue', linetype='solid') +
  geom_point(color='blue', shape=19) +
  ylab('Time (s)') +
  xlab('Threads') +
  scale_x_continuous(breaks = c(0,ThreadData$threads), expand = c(0, 0), trans='log10') +
  expand_limits(x = 0, y = c(0,60000)) +
  scale_y_continuous(expand = c(0, 0)) +
  coord_cartesian(clip = "off") +
  ggsave("ThreadStepTo512.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")


############## 
# - Fig 3D - #
##############

system('cd /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
setwd('/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
files <- c("./performance/Performance_Fig3D.tsv")
ThreadData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerThreadData)
summarise(ThreadData)
ThreadData
ThreadData$threads <- as.numeric(as.character(ThreadData$threads))
ThreadData$time_s <- as.numeric(as.character(ThreadData$time_s))


p_line_thread_by_time <- ggplot(data=ThreadData,aes(x = threads, y = time_s),na.rm=TRUE) 
p_line_thread_by_time + 
  my.theme2 +
  geom_line(color='blue', linetype='solid') +
  geom_point(color='blue', shape=19) +
  ylab('Time (s)') +
  xlab('Threads') +
  scale_x_continuous(expand = c(0, 0)) +
  expand_limits(x = 0, y = c(0,60000)) +
  scale_y_continuous(expand = c(0, 0)) +
  coord_cartesian(clip = "off") +
  ggsave("ThreadStepTo16000.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")


#######################################
# - Fig 3C - Combined Large + Small - #
#######################################

system('cd /Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
setwd('/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/')
files <- c("./performance/Performance_Fig3C_combined.tsv")
ThreadData <- read.csv(file.path(files), sep='\t', header=TRUE)
dim(KmerThreadData)
summarise(ThreadData)
ThreadData
ThreadData$threads <- as.numeric(as.character(ThreadData$threads))
ThreadData$time_s <- as.numeric(as.character(ThreadData$time_s))


p_line_thread_by_time <- ggplot(data=ThreadData,aes(x = threads, y = time_s),na.rm=TRUE) 
p_line_thread_by_time + 
  my.theme2 +
  geom_line(color='blue', linetype='solid') +
  geom_point(color='blue', shape=19) +
  ylab('Time (s)') +
  xlab('Threads') +
  scale_x_continuous(breaks = c(0,ThreadData$threads), expand = c(0, 0), trans='log2') +
  coord_cartesian(clip = "off") +
  geom_text(aes(label=time_s),hjust=1, vjust=0, check_overlap = TRUE) +
  theme(axis.text.x = element_text(angle = 90, hjust = 1)) +
  ggsave("ThreadStepCombinedLog10.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")



# - Fig 4 - #

# Redoing this figure with the altered parameters for uniqueness and max occ
#files3 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper.tsv")

# Resubmission - September 26 2020
#iles3 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_Cytoscan_FTSearch_k31s10m200u_countspluskmers_Full.tsv")
#files3 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/cytoscan/ERR1955491_Cytoscan_FTSearch_UniqReads_k31s10m150u_WithBamQuery.tsv")
#files3 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_Cytoscan_FTSearch_k31s5m150u_PaperFinal.tsv")
files3 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_Cytoscan_FTSearch_Paper_k31s10m200u_Final.tsv")

# Read csv into data frame
CountData <- read.csv(file.path(files3), sep='\t',header=TRUE)
dim(CountData)
summarise(CountData)
date <- Sys.Date()
date

# Convert relevant text columns to ints. Note, these are hard-coded to the column headers in the output files as of 20190925
CountData$Ref_Count <- as.numeric(as.character(CountData$Ref_Count))
CountData$Alt_Count <- as.numeric(as.character(CountData$Alt_Count))
CountData$RefCoverageFromBam <- as.numeric(as.character(CountData$RefCoverageFromBam))
CountData$AltCoverageFromBam <- as.numeric(as.character(CountData$AltCoverageFromBam))
# Make another column as the sum of ref and alt from flex typer
CountData$TotalFlexTyper <- CountData$Ref_Count + CountData$Alt_Count 

# Make the deltas, accounting for instances where both are 0
CountData$DeltaRef <- ifelse((CountData$Ref_Count == 0 & CountData$RefCoverageFromBam==0), NA, CountData$Ref_Count-CountData$RefCoverageFromBam)
# Repeat for delta Alt
CountData$DeltaAlt <- ifelse((CountData$Alt_Count == 0 & CountData$AltCoverageFromBam==0), NA, CountData$Alt_Count-CountData$AltCoverageFromBam)
# Repeat for delta Total
CountData$DeltaTotal <- ifelse((CountData$TotalFlexTyper == 0 & CountData$TotalCoverageFromBam==0), NA, CountData$TotalFlexTyper-CountData$TotalCoverageFromBam)

# Re-sort by chromosome and then position
CountData <- CountData[order(CountData$Chrom, CountData$Pos),]


cor(CountData$TotalCoverageFromBam,CountData$TotalFlexTyper,method = "spearman")






# Begin to plot, set some stuff up
my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
my.theme2 <- theme_classic()  + theme(aspect.ratio = 1/4) + theme(legend.position="bottom")
# coverageBamFlexTyperRef <- function(my.theme) {
#     # Make basic plot as p, comparing ref coverage from bam and ref_count from FlexTyper
#     p_ref_scatter <- ggplot(data=CountData,aes(x = RefCoverageFromBam, y = Ref_Count),na.rm=TRUE)
#     p_ref_scatter         + 
#       my.theme          + 
#       xlim(1,100)       + 
#       ylim(1,100)       + 
#       geom_point(alpha=0.01,size=3,shape=20) + 
#       geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
#       xlab('Reference Coverage From Bam') +
#       ylab('Reference Count From FlexTyper')
#     ggsave("RefCoverageScatter.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
# }
# 
# coverageBamFlexTyperAlt <- function(my.theme) {
# 	# Repeat for alt coverage
# 	p_alt_scatter <- ggplot(data=CountData,aes(x = AltCoverageFromBam, y = Alt_Count),na.rm=TRUE)
# 	p_alt_scatter     + 
# 	  my.theme          +
#   	xlim(1,100)       + 
# 	  ylim(1,100)       +
# 	  geom_point(alpha=0.01,size=3,shape=20) +
# 	  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
# 	  xlab('Alternate Coverage From Bam') +
# 	  ylab('Alternate Count From FlexTyper')
# 	ggsave("AltCoverageScatter.pdf",plot= last_plot(),path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
# }

totalCoverageScatterBamFlexTyper <- function(my.theme) {
	# And total coverage
	p_total_scatter <- ggplot(data=CountData,aes(x = TotalCoverageFromBam, y = TotalFlexTyper),na.rm=TRUE)
	p_total_scatter   + 
	  my.theme 	  +
	  xlim(1,100) 	  + 
	  ylim(1,100) 	  +
	  geom_bin2d(bins=100) + 
	  scale_fill_gradient(low="lightblue1",high="darkblue",trans="log10") + 
	  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
	  xlab('Total Coverage From Bam') +
	  ylab('Total Count From FlexTyper')
	ggsave(paste("TotalCoverageScatter", date,".pdf",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
	ggsave(paste("TotalCoverageScatter", date,".png",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
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
	ggsave(paste("TotalPositionalBoth", date, ".pdf",sep=""),plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
	ggsave(paste("TotalPositionalBoth", date, ".png",sep=""),plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
}

deltasAlongPosAxisTot <- function(my.theme) {
	# Plot the delta along the positional axis, centered on 0 for y 
	p_pos_delta_total <- ggplot(data=CountData[CountData$Chrom=='1',], aes(x=Pos, y=DeltaTotal))
	p_pos_delta_total + 
	  my.theme 	  +
	  ylim(-50,50) 	  +
	  geom_point(alpha=0.05,rasterized=TRUE) +
	  geom_abline(linetype=2,slope=0,intercept=0,color='black') +
	  xlab('Chromsomal Position [chromosome 1]')
	ggsave(paste("DeltaTotalPositional", date, ".pdf",sep=""),plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
	ggsave(paste("DeltaTotalPositional", date, ".png",sep=""),plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
}

# deltaAlongPosAxisAlt <- function(my.theme) {
# 	# Plot the delta along the positional axis, centered on 0 for y 
# 	p_pos_delta_alt <- ggplot(data=CountData[CountData$Chrom=='1',], aes(x=Pos, y=DeltaAlt))
# 	p_pos_delta_alt  + 
# 	  my.theme 	 +
# 	  ylim(-50,50) 	 +
# 	  geom_point(alpha=0.05,color='red') +
# 	  geom_abline(linetype=2,slope=0,intercept=0,color='red') +
# 	  xlab('Chromsomal Position [chromosome 1]')
# 	ggsave("DeltaAltPositional.pdf",plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
# }
# 
# deltaAlongPosAxisRef <- function(my.theme) {
# 	# Plot the delta along the positional axis, centered on 0 for y 
# 	p_pos_delta_ref <- ggplot(data=CountData[CountData$Chrom=='1',], mapping=aes(x=Pos, y=DeltaRef))
# 	p_pos_delta_ref  + 
# 	  my.theme 	 +
# 	  ylim(-50,50) 	 +
# 	  geom_point(alpha=0.05,color='blue') +
# 	  geom_abline(linetype=2,slope=0,intercept=0,color='red') +
# 	  xlab('Chromsomal Position [chromosome 1]')
# 	ggsave("DeltaRefPositional.pdf",plot= last_plot(), height=5, width=15, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
# }

# deltas_histogram_ref <- function(my.theme) {
# 	# Plot a histogram of the deltas
# 	p_delta_hist <- ggplot(data=CountData)
# 	p_delta_hist 	 +
# 	  my.theme 	 + 
# 	  xlim(-50,50) 	 +
# 	  geom_histogram(binwidth=2,aes(DeltaRef,color="Reference"),alpha=0.05) +
# 	  xlab('Delta between FlexTyper - BamCoverage')
# 	ggsave("DeltaHistBoth.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
# }

deltas_histogram_both <- function(my.theme) {
	# Plot a histogram of the deltas
	p_delta_hist <- ggplot(data=CountData)
	p_delta_hist 	 +
	  my.theme 	 + 
	  xlim(-25,25) 	 +
	  geom_histogram(binwidth=0.5,aes(DeltaRef,color="Reference"),bins=25,alpha=0.05) +
	  geom_histogram(binwidth=0.5,aes(DeltaAlt,color="Alternate"),bins=25,alpha=0.05) +
	  xlab('Delta between FlexTyper - BamCoverage')
	ggsave(paste("DeltaHistBoth.pdf",date,".pdf",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
	ggsave(paste("DeltaHistBoth.pdf",date,".png",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
}

deltas_histogram_both_highCount <- function(my.theme) {
  # Plot a histogram of the deltas
  p_delta_hist <- ggplot(data=CountData)
  p_delta_hist 	 +
    my.theme 	 + 
    xlim(10,2000) 	 +
    geom_histogram(binwidth=50,aes(DeltaRef,color="Reference"),bins=25,alpha=0.05) +
    geom_histogram(binwidth=50,aes(DeltaAlt,color="Alternate"),bins=25,alpha=0.05) +
    xlab('Delta between FlexTyper - BamCoverage') 
  ggsave(paste("DeltaHistBothHighCount", date, ".pdf",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
  ggsave(paste("DeltaHistBothHighCount", date, ".png",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
}


# __main__ calls
#coverageBamFlexTyperRef(my.theme)
#coverageBamFlexTyperAlt(my.theme)
totalCoverageScatterBamFlexTyper(my.theme)
posAlongXAxisTotalFlexTyperonY(my.theme2)
deltasAlongPosAxisTot(my.theme2)
#deltaAlongPosAxisRef(my.theme2)
#deltas_histogram_ref(my.theme)
deltas_histogram_both(my.theme)
#deltaAlongPosAxisAlt(my.theme2)
deltas_histogram_both_highCount(my.theme)

## Investigating High query counts ##

bigQueriesFile <- "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper_k31s10m200u_OddQueryCounts.tsv"
regQueriesFile <- "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper_k31s10m200u_RegularQueryCounts.tsv"
biggerThanBamQueriesFile <- "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper_k31s10m200u_BiggerThanBam10.tsv"
#bigQueriesFile <- "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper_k31s10m200u_OddQueryCounts.tsv"
#regQueriesFile <- "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper_k31s10m200u_RegularQueryCounts.tsv"

head(CountData)

RegQueriesDF <- CountData %>%
 filter(DeltaTotal >= -10 & DeltaTotal <= 10)
write_tsv(RegQueriesDF, path = regQueriesFile)

OverCountDF <- CountData %>%
  filter(DeltaTotal>=10)
write_tsv(OverCountDF, path=biggerThanBamQueriesFile)

BigQueriesDF <- CountData %>%
  filter(DeltaTotal > 100)
write_tsv(BigQueriesDF, path = bigQueriesFile)


BigQueriesDF

# Check for offending kmers
BigQueriesDF <- CountData %>%
  filter()












## Comparing hits between different runs ##
filesA <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/cytoscan/ComparingCountsFlexTyper_ERR1955491_k31s10m200u_k50s5m150u.tsv")
# <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_FlexTyper.tsv")
#filesB <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/ERR1955491_SProbe_WithBamQuery_maxOcc100_requireUnique.tsv")
filesA <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/cytoscan/ComparingCountsFlexTyper_ERR1955491_k31s10m200u_k31s10m150uUniqRead.tsv")
# Read csv into data frame
CountDataA <- read.csv(file.path(filesA), sep='\t',header=TRUE)
dim(CountDataA)
summarise(CountDataA)

# Convert relevant text columns to ints. Note, these are hard-coded to the column headers in the output files as of 20190925
CountDataA$k31s10m200u_Ref <- as.numeric(as.character(CountDataA$k31s10m200u_Ref))
CountDataA$k31s10m200u_Alt <- as.numeric(as.character(CountDataA$k31s10m200u_Alt))
CountDataA$k31s10m150uUniq_Ref <- as.numeric(as.character(CountDataA$k31s10m150uUniq_Ref))
CountDataA$k31s10m150uUniq_Alt <- as.numeric(as.character(CountDataA$k31s10m150uUniq_Alt))

# Plot A vs. B for Delta
totalCoverageScatterFlexTyperDiffRuns <- function(my.theme) {
  # And total coverage
  p_total_scatter <- ggplot(data=CountDataA,aes(x = k31s10m200u_Ref, y = k31s10m150uUniq_Ref),na.rm=TRUE)
  p_total_scatter   + 
    my.theme 	  +
    xlim(1,100) 	  + 
    ylim(1,100) 	  +
    geom_bin2d(bins=100) + 
    scale_fill_gradient(low="lightblue1",high="darkblue",trans="log10") + 
    geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
    xlab('Unique Reads Off k31s10m200u_Ref') +
    ylab('Unique Reads On k31s10m150uUniqRef')
  ggsave("TotalCoverageScatter_Ref_Differences.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/PlottingOutput/")
}

totalCoverageScatterFlexTyperDiffRuns(my.theme)





### African Contigs ###
## October 5th 2020 ##
my.theme <- theme_classic()  + theme(aspect.ratio = 1) + theme(legend.position="bottom")
filesAfrican <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/CombinedAfrican_UniqReads_k50s10m100u.tsv")
CountDataA <- read.csv(file.path(filesAfrican), sep='\t',header=TRUE,row.names = "INfo")
CountDataA$EUR_Father <- as.numeric(as.character(CountDataA$EUR_Father))
CountDataA$EUR_Mother <- as.numeric(as.character(CountDataA$EUR_Mother))
CountDataA$EUR_Kid <- as.numeric(as.character(CountDataA$EUR_Kid))
CountDataA$EAS_Father <- as.numeric(as.character(CountDataA$EAS_Father))
CountDataA$EAS_Mother <- as.numeric(as.character(CountDataA$EAS_Mother))
CountDataA$EAS_Kid <- as.numeric(as.character(CountDataA$EAS_Kid))
CountDataA$AFR_Father <- as.numeric(as.character(CountDataA$AFR_Father))
CountDataA$AFR_Mother <- as.numeric(as.character(CountDataA$AFR_Mother))
CountDataA$AFR_Kid <- as.numeric(as.character(CountDataA$AFR_Kid))
CountDataA$AFR_Father <- as.numeric(as.character(CountDataA$AFR_Father))

#CountDataA$DeltaCount <- CountDataA$AFR_Father - CountDataA$EUR_Father

dim(CountDataA)
meta <- read.csv(file.path("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/OpenFlexTyper/manuscript/african/meta.tsv"),header=TRUE,sep='\t')
meta

# Let's look at counts where it's high in one pop and low in another



# Plot A vs. B for Delta
  # And total coverage
p_total_scatter <- ggplot(data=CountDataA,aes(x = EUR_Father, y = AFR_Father),na.rm=TRUE)
p_total_scatter   + 
  my.theme +
  xlim(1,5000) 	  + 
  ylim(1,5000) 	  +
  geom_bin2d(bins=100) + 
  scale_fill_gradient(low="darkblue",high="lightblue1",trans='log10') + 
  xlab('African Contig Coverage (European)') +
  ylab('African Contig Coverage (African)') +
  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
ggsave("AfricanContigCoverageScatterEURfather_vs_AFRfather.png",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")


p_total_scatter <- ggplot(data=CountDataA,aes(x = EUR_Father, y = EUR_Mother),na.rm=TRUE)
p_total_scatter   + 
  my.theme +
  xlim(1,5000) 	  + 
  ylim(1,5000) 	  +
  geom_bin2d(bins=100) + 
  scale_fill_gradient(low="lightblue1",high="darkblue",trans="log10") + 
  xlab('African Contig Coverage (European father)') +
  ylab('African Contig Coverage (European mother)') +
  geom_abline(linetype=2,slope=1, intercept=0, show.legend = TRUE,color='#E41A1C') +
  ggsave("AfricanContigCoverageScatter_EURfather_vs_EURmother.png",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")

# Plot all
plot(CountDataA, pch = 20, col = alpha('black')) +
  geom_bin2d(bins=100) + 
  scale_fill_gradient(low="lightblue1",high="darkblue",trans="log10") +
  ggsave("PairwiseAfricanAnalyses2.png",plot=last_plot(),path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")


# Filter 
AFR_uniq <- CountDataA %>%
  filter((EUR_Father < 5) & (EUR_Mother <5 ) & (EUR_Kid < 5) & 
           (EAS_Father < 5) & (EAS_Mother <5 ) & (EAS_Kid < 5) & 
           (AFR_Father > 10) & (AFR_Mother > 10 ) & (AFR_Kid > 10)) 

nrow(AFR_uniq)

EUR_uniq <- CountDataA %>%
  filter((AFR_Father > 5) & (AFR_Mother <5 ) & (AFR_Kid < 5) & 
           (EAS_Father < 5) & (EAS_Mother <5 ) & (EAS_Kid < 5) & 
           (EUR_Father > 10) & (EUR_Mother > 10 ) & (EUR_Kid > 10)) 
nrow(EUR_uniq)


EAS_uniq <- CountDataA %>%
  filter((EUR_Father < 5) & (EUR_Mother <5 ) & (EUR_Kid < 5) & 
           (AFR_Father < 5) & (AFR_Mother <5 ) & (AFR_Kid < 5) & 
           (EAS_Father > 10) & (EAS_Mother > 10 ) & (EAS_Kid > 10)) 
nrow(EAS_uniq)
library(RColorBrewer)
install.packages("heatmap3")
library(heatmap3)

CombinedUniq <- as.matrix(bind_rows(AFR_uniq, EUR_uniq, EAS_uniq))


pdf(file="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/AfricanHeatmap.pdf")
pheatmap(log(CombinedUniq+1),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/AfricanUniqContigs_pheatmap.pdf",cluster_rows = FALSE)
dev.off()
#heatmap(CombinedUniq, col= colorRampPalette(brewer.pal(8, "Oranges"))(25))
#legend(x="right",legend=c("min", "max"),col= par("col"))




ggsave(paste("AfricanHeatmap",date,".pdf",sep=""),plot= h, path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")


write_tsv(CombinedUniq, path = "/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/CombinedUniq.tsv")

p_hist_all <- ggplot(data=CountDataA)
p_hist_all 	 +
  my.theme 	 + 
  xlim(0,500) 	 +
  ylim(0,20000) +
  geom_histogram(binwidth=0.5,aes(EUR_Father,color="red"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(EUR_Mother,color="red"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(EUR_Kid,color="red"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(AFR_Father,color="blue"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(AFR_Mother,color="blue"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(AFR_Kid,color="blue"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(EAS_Father,color="green"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(EAS_Mother,color="green"),bins=25,alpha=0.0001) +
  geom_histogram(binwidth=0.5,aes(EAS_Kid,color="green"),bins=25,alpha=0.0001) +
  xlab('Coverage') 
ggsave(paste("AfricanHistAll.pdf",date,".pdf",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")
ggsave(paste("AfricanHistAll.png",date,".png",sep=""),plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")





# Heatmap
pheatmap(log10((CountDataA +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/AfricanFullHeatmap.png")  




# October 23rd 2020 - HLA GRCh38 stuff
# Here I'm working with some HLA GRCh38 stuff
# Reading in the file
#fileHLA <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/CollatedGRCh38_Alts.csv")
fileHLAgrch38 <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/CollatedGRCh38_Alts_k31s1m150u.csv")

HLACounts <- read.csv(file.path(fileHLAgrch38), sep=',',header=TRUE)
HLACounts$Count <- as.numeric(as.character(HLACounts$Count))
HLACounts

# Meta data file describing samples and ethnicities
metaDataFile <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/SampleMetadata.csv")
meta <- read.csv(file.path(metaDataFile), sep=',',header=TRUE)
meta

# Make a big joined table
BigjoinedTable <- HLACounts %>%
  left_join(meta, by = "SampleID") 
write.table(BigjoinedTable, file='/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/HLA_GRCh38_JoinedWithMeta.csv', quote=FALSE, sep=',', row.names = FALSE)

# Make a wider version of this table
DataMatrix <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID")



# Select from that table
GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter(Gene=="") %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/A-3105_Alleles_LogScale_GRCh38.png")  





# October 26th, 2020 
# This one is the major alleles
fileHLA <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/CollatedMajorAlleles_k31s1m150u.csv")

HLACounts <- read.csv(file.path(fileHLA), sep=',',header=TRUE)
HLACounts$Count <- as.numeric(as.character(HLACounts$Count))
HLACounts

# Meta data file describing samples and ethnicities
metaDataFile <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/SampleMetadata.csv")
meta <- read.csv(file.path(metaDataFile), sep=',',header=TRUE)
meta

# Make a big joined table
BigjoinedTable <- HLACounts %>%
  left_join(meta, by = "SampleID") 
write.table(BigjoinedTable, file='/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/HLA_GRCh38_JoinedWithMeta.csv', quote=FALSE, sep=',', row.names = FALSE)

# Make a wider version of this table
DataMatrix <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID")



# Select from that table
GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter(Gene=="A") %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/A_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  

# Select from that table
GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter(Gene=="DRB1") %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/DRB1_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  

# Select from that table
GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter(Gene=="DPB1") %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/DPB1_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  

# Select from that table
GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter(Gene=="W") %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/W_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  



GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="DPA1")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/DPA1_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  


GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="MICA")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/MICA_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  



GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="MICB")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/MICB_Alleles_LogScale_MajorAlleles.pdf",cluster_rows = FALSE)  


GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="W")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/W_Alleles_LogScale_MajorAlleles.png")  

GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="Y")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/Y_Alleles_LogScale_MajorAlleles.png")  

GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="DQB1")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/DQB1_Alleles_LogScale_MajorAlleles.png")  

GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="A")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/A_Alleles_LogScale_MajorAlleles.png")  

GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="B")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/B_Alleles_LogScale_MajorAlleles.png")  

GeneFilteredTable <- BigjoinedTable %>%
  arrange(Ethnicity) %>%
  filter((Gene=="C")) %>%
  pivot_wider(id_cols = c(QueryID),
              names_from = SampleName,
              values_from = Count) %>%
  remove_rownames %>%
  column_to_rownames(var="QueryID") 
# Plot the gene
pheatmap(log10(t(GeneFilteredTable +1)),filename="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/C_Alleles_LogScale_MajorAlleles.png")  



# Some plotting
data_umap <- umap(DataMatrix)
plot(data_umap)

pheatmap(t(DataMatrix), NA.rm=TRUE, log=TRUE)

# Plot
ggplot(data=joinedTable, aes(x=SampleName,y=count)) +
  geom_bar() 
  
joinedTable


# Data for Fig 3 - Mixed Patient Analysis, Alice ended up doing most of this
# October 27 2020
fileMixedVirus <- c("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/MixedViralAnalysis.tsv")

ViralCounts <- read.csv(file.path(fileMixedVirus), sep='\t',header=TRUE)
ViralCounts$count <- as.numeric(as.character(ViralCounts$count))
ViralCounts$Expect_SE <- as.numeric(as.character(ViralCounts$Expect_SE))
ViralCounts$Expect_PE <- as.numeric(as.character(ViralCounts$Expect_PE))
ViralCounts$C <- as.numeric(as.character(ViralCounts$C))
ViralCounts$K2 <- as.numeric(as.character(ViralCounts$K2))


grouped <- ViralCounts %>%
  group_by(k,s,UniqK,UniqRead) %>%
  ggplot(aes(x=Sample,y=count)) 
  

  
  
  




# African Contig Histograms
library(RColorBrewer)
library(reshape2)
library(viridisLite)
library(grid)
library(ggplot2)
library(cowplot)
#library(ggplotify)

AFR <- read.csv("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/AFR.csv")
EAS <- read.csv("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/EAS.csv")
EUR <- read.csv("/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/EUR.csv")

df.AFR <- melt(AFR,id.vars = c("Info"))
df.EUR <- melt(EUR,id.vars = c("Info"))
df.EAS <- melt(EAS,id.vars = c("Info"))

p.AFR <- ggplot(df.AFR, aes(x = value, fill= variable)) + 
  theme(plot.title = element_text(hjust = 0.5),
        axis.ticks = element_blank(),  
        axis.line = element_line(size = 0.3, colour = "black"),   
        axis.title.x = element_blank(),panel.background=element_blank(),  
        legend.position = c(0.8, 0.8),legend.title = element_blank(),
        axis.text.x = element_text(angle = 90)) + 
  geom_density(aes(y = log10(..count.. + 1)), alpha =0.9, color=NA) + 
  scale_x_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_y_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_fill_brewer(palette="Dark2") + 
  labs(title="AFR", y="Log10(Count)")

p.EUR <- ggplot(df.EUR, aes(x = value, fill= variable))  + 
  theme(plot.title = element_text(hjust = 0.5), 
        axis.ticks = element_blank(), 
        axis.line = element_line(size = 0.3, colour = "black"), 
        axis.title.x = element_blank(),
        panel.background=element_blank(), 
        legend.position = c(0.8, 0.8), 
        legend.title = element_blank(),
        axis.text.x = element_text(angle = 90)) + 
  geom_density(aes(y = log10(..count.. + 1)), alpha =0.9, color=NA) + 
  scale_x_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_y_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_fill_brewer(palette="Dark2") + labs(title="EUR", y="Log10(Count)")

p.EAS <- ggplot(df.EAS, aes(x = value, fill= variable))  + 
  theme(plot.title = element_text(hjust = 0.5), 
        axis.ticks = element_blank(), 
        axis.line = element_line(size = 0.3, colour = "black"), 
        axis.title.x = element_blank(),panel.background=element_blank(), 
        legend.position = c(0.8, 0.8), legend.title = element_blank(),
        axis.text.x = element_text(angle = 90)) + 
  geom_density(aes(y = log10(..count.. + 1)), alpha =.9, color=NA) + 
  scale_x_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_y_continuous(expand = expansion(mult = c(0, 0))) + 
  scale_fill_brewer(palette="Dark2") + 
  labs(title="EAS", y="Log10(Count)")

plot_grid(p.AFR,p.EUR,p.EAS, ncol =3,rel_widths = 8)
ggsave("AfricanHistograms.pdf",plot= last_plot(), path="/Users/philliprichmond/Dropbox/Grad_School/FlexTyper/")



