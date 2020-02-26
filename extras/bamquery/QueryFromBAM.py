import argparse
import os
import sys
import math
import pysam
from pybedtools import BedTool
from string import maketrans



# I didn't actually write this function, Aaron Odell did, but I've made modifications and a couple comments
class Variant:
	def __init__(self,chromosome,position,samfile):
		self.chromosome = chromosome
		self.position = position
		self.samfile = samfile
	def getInfo(self):
		### Here we are utilizing the pysam pileupcolumn object which is filled with pileupread objects which are filled with aligment objects
		self.nucDict = {'A':0,'C':0,'T':0,'G':0,'N':0}
		self.coverage = 0
		self.indelReads = 0
		#print '#################newVar############################'
		for pileupcolumn in self.samfile.pileup(self.chromosome,self.position-1,self.position+1):
			if pileupcolumn.pos == (self.position-1):
				for pileUpRead in pileupcolumn.pileups:
					if pileUpRead.is_del == 1:
						self.indelReads = self.indelReads + 1
                                                self.coverage = self.coverage + 1
					else:
						self.nucDict[pileUpRead.alignment.seq[pileUpRead.query_position]] = self.nucDict[pileUpRead.alignment.seq[pileUpRead.query_position]] + 1
						self.coverage = self.coverage + 1
				self.ann = self.chromosome+'\t'+str(self.position)+'\t'+'Coverage:'+str(self.coverage)+'\t'
				for i in self.nucDict:
					self.ann = self.ann+i+":"+str(self.nucDict[i])+'\t'
				self.ann = self.ann+"INDELReads:"+str(self.indelReads)
				break
			elif pileupcolumn.pos > (self.position + 10):
				break
		if self.coverage == 0:
			self.ann = self.chromosome+'\t'+str(self.position)+'\t'+'Coverage:'+str(self.coverage)+'\t'+'A:0'+'\t'+'C:0'+'\t'+'T:0'+'\t'+'G:0'+'\t'+'N:0'+'\t'+'INDELReads:'+str(self.indelReads)


#def GetNucDictFromBAM(BAM,CHROM,POS):
#    samfile = pysam.AlignmentFile(BAM,"rb")
#    for pileupcolumn in samfile.pileup(CHROM,POS,POS+1):
#        print "coverage is %d"%pileupcolumn.n
#        for pileupread in pileupcolumn.pileups:
#            if not pileupread.is_del and not pileupread.is_refskip:
#                # query position is None if is_del or is_refskip is set.
#                print ('\tbase in read %s = %s' % (pileupread.alignment.query_name,pileupread.alignment.query_sequence[pileupread.query_position]))
#                samfile.close()



def CoverageFromQuery(ARGS):

"""
This function will take in the bam file, and read the coverage over positions as defined by the input.tsv files.

Input tsv files are in standardized format:
#Index Reference   Alternate   Chrom   Pos Ref Alt Identifier  DataType
0   TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCTTACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGAAAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT   TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCTTACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACACTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGAAAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT   16  27557749    T   C   rs7198785_S-3AAAA   cytoscan

# It will then produce an output which adds a coverage for ref and alt bases
"""
        query = open(ARGS.Query,'r')
        outFile = open(ARGS.o,'w')
	
	# Open the bam file
        samfile = pysam.Samfile(ARGS.bam,"rb")		
        
        # output TSV will have this header
	outFile.write("#Index\tReference\tAlternate\tChrom\tPos\tRef\tAlt\tIdentifier\tDataType\tRefCoverageFromBam\tAltCoverageFromBam\tTotalCoverageFromBam\n")
	for line in query:
		line = line.strip('\r')
                line = line.strip('\n')
                if line[0] != '#':
			columns = line.split('\t')
			chromosome = columns[3]
                        if ARGS.Genome=='hg19': 
                            chromosome = 'chr'+chromosome
                        elif ARGS.Genome=='GRCh37':
                            chromosome = chromosome
                        else:
                            print "You did not select a viable genome"
                            sys.exit()
                        try:
			    varPos = int(columns[4])
                        except:
                            continue
                        refBase = columns[5]
                        altBase = columns[6]
			#populate the variant class
			varMan = Variant(chromosome,varPos,samfile)

			try:
				varMan.getInfo()
			except(ValueError):
				outFile.write("%s\t.\t.\n"%(line))
                                continue
                        if altBase != '.':
                            AltCount = varMan.nucDict[altBase]
                        else:
                            AltCount = 0
                        RefCount = varMan.nucDict[refBase]
                        Coverage = varMan.coverage
			outFile.write("%s\t%d\t%d\t%d\n"%(line,RefCount,AltCount,Coverage))

if __name__  == "__main__":	
	parser = argparse.ArgumentParser()
	parser.add_argument("-bam",help="input your bam file",type=str)
	parser.add_argument("-o",help="name of the ouput file",type=str)
	parser.add_argument("--ID",help="name of the sample ID",type=str)
        parser.add_argument("-Q","--Query",help="name of your input query file. Usually either SProbe_Cyto_Merged.cytoquery.tsv or CProbe_Cyto_Merged.cytoquery.tsv",type=str)
        parser.add_argument("-G","--Genome",help="Either choose hg19 || GRCh37",required=True)

	args = parser.parse_args()
        CoverageFromQuery(args)

