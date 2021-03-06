#!/usr/bin/perl
use strict;
use warnings;

my $scoreCalcDir = "/home/users/msoni/Desktop/manoj_gatech/research/gtfold/scoring_code_shel/shelswenson-gtfold-cdc688c/rna-scoring";
my $seqDir = $scoreCalcDir."/d0d2dScomparison/sequences";
my $scoreCalcPrg = $scoreCalcDir."/RNAScoring";

my $gtfoldBaseDir = "/home/users/msoni/Desktop/manoj_gatech/research/gtfold/git_code/gtfold/gtfold-mfe";
my $gtfoldPrg = $gtfoldBaseDir."/src/gtfold";

my $easyoutfilepath = $seqDir."/easy/d0d2dScomparison.txt";

my $easyseq1=$seqDir."/easy/biloba.seq";

#----------------------------------------
#arboreum.seq  canicula.seq  ecoli.seq  hsapiens.seq  volcanii.seq
$easyseq1=$seqDir."/hard/arboreum.seq";
generateResult($easyseq1,$easyoutfilepath);

$easyseq1=$seqDir."/hard/canicula.seq";
generateResult($easyseq1,$easyoutfilepath);

$easyseq1=$seqDir."/hard/ecoli.seq";
generateResult($easyseq1,$easyoutfilepath);

$easyseq1=$seqDir."/hard/hsapiens.seq";
generateResult($easyseq1,$easyoutfilepath);

$easyseq1=$seqDir."/hard/volcanii.seq";
generateResult($easyseq1,$easyoutfilepath);

#----------------------------------------


sub generateResult{
 my($seq,$out)=@_;
 #my $str="Score is\n";
 #`echo $str`;
my $cmd = "$gtfoldPrg $seq";
#print($cmd);
`$cmd`;
# `$scoreCalcPrg -d0 $seq >> $out`;
# `$scoreCalcPrg $seq >> $out`;
# `$scoreCalcPrg -dS $seq >> $out`;
# `$scoreCalcPrg -d2 $seq >> $out`;
}
