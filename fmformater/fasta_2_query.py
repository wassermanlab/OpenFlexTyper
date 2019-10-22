import datetime
import sys
import argparse
from Bio import SeqIO


def parse_arguments():
    """Parses inputted arguments as described."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-f', '--fasta', help="Fasta file to turn to query", type=str, required=True)
    parser.add_argument('-n', '--filename',
                        help='name of query file generated',
                        type=str, default=(datetime.datetime.now().isoformat()+".tsv"))
    parser.add_argument('-d', '--data_type',
                        help='where the data came from',
                        type=str, default="fasta")                    
    args = parser.parse_args()
    return args

def write_table(fasta, table_name, data_type):
    """writes the final table parsing each variant tuple line by line."""
    query_table = open(table_name, "w+")
    query_table.write("\t".join(["#Index", "Reference Seq", "Info\n"]))
    counter = 0

    for record in SeqIO.parse(fasta, "fasta"):
        record_id = record.id.split("|")
        record_id = ":".join(record_id)
        line = [counter, record.seq, record_id]
        query_table.write("\t".join(map(str, line)))
        query_table.write("\n")
        counter = counter + 1
    query_table.close()

def main():
    args = parse_arguments()
    fasta = args.fasta
    table_name = args.filename
    data_type = args.data_type
    write_table(fasta, table_name, data_type)


if __name__ == "__main__":
    main()

# python utilities/fasta_2_query.py -f multi.fasta.txt