#You need the cairo package from CRAN installed.
#If this is not possible, change svg("stats.svg") e.g. to jpeg("stats.jpg")
#Use with a 2-column stats.dat
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
svg("2d-graph.svg")
plot(x=d$Blocknum,
y=d$Bitcount,
type="l",
col=heat.colors(length(d$Blocknum)),
main="Binary file analysis results") 
dev.off()
title(main="Binary file analysis results")
q()