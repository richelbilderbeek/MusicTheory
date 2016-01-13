#include "musictheorymenudialog.h"

int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::MusicTheoryMenuDialog d;
  d.Execute(args);
}


library(ape)
library(data.table)
library(DDD)
library(geiger)
library(nLTT)
library(PBD)
library(phangorn)
library(phytools)
library(plyr)
library(RColorBrewer)
library(testit)

source("~/GitHubs/R/FileIo/get_base_filename.R")
source("~/GitHubs/R/MyFavoritePackages/olli_rBEAST/R/fun.beast2output.R")
source("~/GitHubs/R/MyFavoritePackages/olli_rBEAST/R/fun.beast2.R")
source("~/GitHubs/R/MyFavoritePackages/olli_rBEAST/R/fun.beast.R")
source("~/GitHubs/R/MyFavoritePackages/olli_rBEAST/R/fun.treeannotator.R")
source("~/GitHubs/R/MyFavoritePackages/olli_rBEAST/R/script.beast.R")
source("~/GitHubs/R/Peregrine/add_alignments.R")
source("~/GitHubs/R/Peregrine/add_pbd_output.R")
source("~/GitHubs/R/Peregrine/add_posteriors.R")
source("~/GitHubs/R/Peregrine/add_species_trees_with_outgroup.R")
source("~/GitHubs/R/Peregrine/load_parameters_from_file.R")
source("~/GitHubs/R/Peregrine/load_parameters_from_file.R")
source("~/GitHubs/R/Peregrine/save_parameters_to_file.R")
source("~/GitHubs/R/Peregrine/show_posteriors.R")
source("~/GitHubs/R/Peregrine2/do_analyze_alignments.R")
source("~/GitHubs/R/Peregrine2/do_analyze_both_nltts.R")
source("~/GitHubs/R/Peregrine2/do_analyze_nltts_stats.R")
source("~/GitHubs/R/Peregrine2/do_analyze_posterior_average_nltt.R")
source("~/GitHubs/R/Peregrine2/do_analyze_posterior_average_nltts.R")
source("~/GitHubs/R/Peregrine2/do_analyze_posterior_sample_nltts.R")
source("~/GitHubs/R/Peregrine2/do_analyze_posterior_samples.R")
source("~/GitHubs/R/Peregrine2/do_analyze_single_gene_tree.R")
source("~/GitHubs/R/Peregrine2/do_analyze_single_species_tree_with_outgroup.R")
source("~/GitHubs/R/Phylogenies/add_outgroup_to_phylogeny.R")
source("~/GitHubs/R/Phylogenies/convert_alignment_to_beast_posterior.R")
source("~/GitHubs/R/Phylogenies/convert_alignment_to_fasta.R")
source("~/GitHubs/R/Phylogenies/convert_phylogeny_to_alignment.R")
source("~/GitHubs/R/Phylogenies/get_average_nltt.R")
