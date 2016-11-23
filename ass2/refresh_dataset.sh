#!/bin/sh
# Script that retrieves a fresh copy of a dataset
dataset="dataset-medium"
rm -rf "$dataset"
unzip "/home/cs2041/public_html/assignments/matelook/$dataset.zip"
./setup_dataset.pl
