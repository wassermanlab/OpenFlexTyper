import pybedtools
import sys
import argparse



def GetArgs():
	parser = argparse.ArgumentParser()
	parser.add_argument("-I","--Infile",help="Infile in the format of Sites: Chrom:position:ref:alt", required=True)
	parser.add_argument("-F","--Fasta",help="Input fasta file corresponding to the positions", required=True)
	parser.add_argument("-O","--Outfile",help="Output file for the queries for FlexTyper", required=True)
	parser.add_argument("-S","--Source",help="Source acquired from,e.g. PeddyGRCh37Sites", required=True)
	args = parser.parse_args()
	return args


# Function which takes in a sites file and produces a query file.
# Sites file looks like (these are 1-based coords):
# 22:50988105:G:A
# 
# Query file looks like:
# #Index	Reference	Alternate	Chrom	Pos	Ref	Alt	Identifier	DataType
#0	TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCTTACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGAAAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT	TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCTTACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACACTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGAAAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT	16	27557749	T	C	rs7198785_S-3AAAA	cytoscan

def ParseSitesGetQuery(SitesInfile,Fasta,QueryOutfile,Source):
	infile = open(SitesInfile,'r')
	outfile = open(QueryOutfile,'w')
	counter = 0
	outfile.write("#Index\tReference\tAlternate\tChrom\tPos\tRef\tAlt\tIdentifier\tDataType\n")
	for line in infile:
		line = line.strip('\n')
		cols=line.split(':')
		chrom = cols[0]
		pos = int(cols[1]) - 1 # 1-based transition
		ref = cols[2]
		alt = cols[3]
		Source='PeddySitesGRCh37'
		refSeq,altSeq = Site2Seqs(chrom,pos,ref,alt,Fasta)
		outfile.write("%d\t%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\n"%(counter,refSeq,altSeq,chrom,pos,ref,alt,line,Source))
		counter += 1

# given 1-based pos coordinate, extract seqs and return the 2 seqs for query, one with the ref and one with the alt alleles
def Site2Seqs(chrom,pos,ref,alt,fasta):
	pos = pos-1
	refSeq = pybedtools.BedTool.seq((chrom,pos-150,pos+151),fasta)
	altSeqleft = pybedtools.BedTool.seq((chrom,pos-150,pos),fasta)
	altSeqright = pybedtools.BedTool.seq((chrom,pos+1,pos+151),fasta)
	altSeq = altSeqleft + alt + altSeqright
	return refSeq,altSeq



def Main():
	ARGS = GetArgs()
	ParseSitesGetQuery(ARGS.Infile,ARGS.Fasta,ARGS.Outfile,ARGS.Source)
	# test Site2Seqs
#	reftest,alttest = Site2Seqs(22,50988105,'G','A',ARGS.Fasta)
#	print(reftest)
#	print(alttest)



if __name__=="__main__":
	Main()

