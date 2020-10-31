import sys
import argparse
import os
import statistics


def parse_arguments():
        """Parses inputted arguments as described"""
        parser = argparse.ArgumentParser()
        parser.add_argument(
                '-f', '--Format', help="format of output", type=str, required=True,
                choices=["VCF", "23_and_me", "ancestry"])
        parser.add_argument(
                '-i', '--Input', help='input tsv ', type=str, required=True)
        parser.add_argument('-n', '--name',
                                                help='name of save file', required=True)
        parser.add_argument("-m", "--minSuppReads", help="Minimum supporting reads for a genotype call", default=1, type=int)
        parser.add_argument("-k", "--kmerFlags", help="If set, then output kmer flags in VCF conversion", action="store_true")
        args = parser.parse_args()
        return args

def flextyper_2_vcf(infilename, name, minSuppReads, kmers):
        """
        This function creates a VCF from output query file.

        It determines genotypes as follows:
                het site: alt>minSuppReads and ref>minSuppReads
                homo alt: alt>minSuppReads and ref<minSuppReads
                homo ref: alt<minSuppReads and ref>minSuppReads
        """
        infile = open(infilename,'r')
        outfile = open("%s.vcf"%name,'w')
        # write the header
        outfile.write("##fileformat=VCFv4.2\n") 
        outfile.write("##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">\n")
        outfile.write("##FORMAT=<ID=AO,Number=A,Type=Integer,Description=\"Alternate allele observation count\">\n")
        outfile.write("##FORMAT=<ID=RO,Number=1,Type=Integer,Description=\"Reference allele observation count\">\n")
        outfile.write("##FORMAT=<ID=DP,Number=1,Type=Integer,Description=\"Read depth\">\n")
        # if offending kmers is turned on, add a tag for the kmers
        if kmers:
            outfile.write("##FORMAT=<ID=ROK,Number=1,Type=String,Description=\"Reference Over Counted Kmers\"\n")
            outfile.write("##FORMAT=<ID=AOK,Number=A,Type=String,Description=\"Alternate Over Counted Kmers\"\n")
            outfile.write("##FORMAT=<ID=RNUK,Number=1,Type=String,Description=\"Reference Non Unique Kmers\"\n")
            outfile.write("##FORMAT=<ID=ANUK,Number=A,Type=String,Description=\"ALTERNATE Non Unique Kmers\"\n")

        # Write a header for the vcf so it can be sorted later
        outfile.write("##contig=<ID=1,length=249250621>\n##contig=<ID=2,length=243199373>\n##contig=<ID=3,length=198022430>\n##contig=<ID=4,length=191154276>\n##contig=<ID=5,length=180915260>\n##contig=<ID=6,length=171115067>\n##contig=<ID=7,length=159138663>\n##contig=<ID=8,length=146364022>\n##contig=<ID=9,length=141213431>\n##contig=<ID=10,length=135534747>\n##contig=<ID=11,length=135006516>\n##contig=<ID=12,length=133851895>\n##contig=<ID=13,length=115169878>\n##contig=<ID=14,length=107349540>\n##contig=<ID=15,length=102531392>\n##contig=<ID=16,length=90354753>\n##contig=<ID=17,length=81195210>\n##contig=<ID=18,length=78077248>\n##contig=<ID=19,length=59128983>\n##contig=<ID=20,length=63025520>\n##contig=<ID=21,length=48129895>\n##contig=<ID=22,length=51304566>\n##contig=<ID=X,length=155270560>\n##contig=<ID=Y,length=59373566>\n##contig=<ID=MT,length=16569>\n")
        outfile.write("#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT\t%s\n"%name)
        for line in infile:
                if line[0]=='#':
                        continue
                cols = line.strip('\n').split('\t')
                chrom = cols[3]
                pos = int(cols[4])  # fixed for 0-based FlexTyper query file format
                ref = cols[5]
                alt = cols[6]
                ID = cols[7]
                ref_count = int(cols[9])
                alt_count = int(cols[10])
                depth = ref_count + alt_count
                if alt_count >= minSuppReads:
                        if ref_count >= minSuppReads:
                                zygosity = '0/1'
                        elif ref_count < minSuppReads:
                                zygosity = '1/1'
                else:
                        zygosity = '0/0'
                # if we are reporting offending kmers
                if(kmers):
                    ROK=cols[11]
                    AOK=cols[12]
                    RNUK=cols[13]
                    ANUK=cols[14]
                    outfile.write("%s\t%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s:%d:%d:%d:%s:%s:%s:%s\n"%(chrom,pos,ID,ref,alt,'.','.','.','GT:RO:AO:DP:ROK:AOK:RNUK:ANUK',zygosity,ref_count,alt_count,depth,ROK,AOK,RNUK,ANUK))
                else:
                    outfile.write("%s\t%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s:%d:%d:%d\n"%(chrom,pos,ID,ref,alt,'.','.','.','GT:RO:AO:DP',zygosity,ref_count,alt_count,depth))
                

def flextyper_2_array(data, name, format):
        if format == "23_and_me":
                new = open(name+"23_and_me.txt", "w+")
                new.write("#rsid\tchromosome\tposition\tgenotype")
        if format == "ancestry":
                new = open(name+"ancestry.txt", "w+")
                new.write("#rsID\tChromosome\tPosition\tAllele 1\tAllele 2\n")
        with open(data) as f:
                for line in f:
                        if not line.startswith("#"):
                                ln = line.split("\t")
                                ln[-1] = ln[-1].rstrip()
                                chrom = ln[3]
                                pos = str(int(ln[4]) + 1)  # making 1 based
                                ID = ln[7]
                                ref = ln[5]
                                alt = ln[6]
                                ref_count = int(ln[9])
                                alt_count = int(ln[10])
                                if alt_count > 0 or ref_count > 0:
                                        if alt_count > 0 and ref_count == 0:  # homozygous alt
                                                allele1 = alt
                                                allele2 = alt
                                        elif alt_count == 0 and ref_count > 0:  # homozygous ref
                                                allele1 = ref
                                                allele2 = ref
                                        elif alt_count > 0 and ref_count > 0:  # het
                                                allele1 = ref
                                                allele2 = alt
                                        if format == "23_and_me":
                                                output = "\t".join([ID, chrom, pos, allele1+allele2])
                                        if format == "ancestry":
                                                output = "\t".join([ID, chrom, pos, allele1, allele2])
                                        new.write(output + "\n")
        new.close()


def main():
        args = parse_arguments()
        Format = args.Format
        Input = args.Input
        minSuppReads = args.minSuppReads
        name = args.name
        kmers = args.kmerFlags

        if Format == "VCF":
                flextyper_2_vcf(Input, name, minSuppReads,kmers)
        if Format == "23_and_me":
                flextyper_2_array(Input, name, "23_and_me")
        if Format == "ancestry":
                flextyper_2_array(Input, name, "ancestry")


if __name__ == "__main__":
        main()
