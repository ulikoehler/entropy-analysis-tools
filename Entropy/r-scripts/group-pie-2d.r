#You need the cairo package from CRAN installed.
#If this is not possible, change svg("stats.svg") e.g. to jpeg("stats.jpg")
#For use with entropy -c
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
svg("stats.svg")
pie(x=d$Count,
labels=d$Number,
angle=45,
col=heat.colors(length(d$Number)),
main="Binary file analysis results") 
dev.off()
q()