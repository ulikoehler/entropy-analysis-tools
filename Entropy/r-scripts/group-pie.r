#You need the cairo package from CRAN installed.
#If this is not possible, change svg("stats.svg") e.g. to jpeg("stats.jpg")
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
svg("stats.svg")
pie(d$Count,
labels=d$Number,
angle=45,
main="Binary file analysis results") 
dev.off()
q()