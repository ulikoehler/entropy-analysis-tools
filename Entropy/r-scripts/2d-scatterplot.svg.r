#You need the cairo package from CRAN installed.
#If this is not possible, change svg("stats.svg") e.g. to jpeg("stats.jpg")
#Use with a 2-column stats.dat
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
svg("2d-scatterplot.svg")
plot(x=d[,1],
y=d[,2],
type="p",
col=heat.colors(length(d[,1])),
main="Binary file analysis results")
dev.off()
q()