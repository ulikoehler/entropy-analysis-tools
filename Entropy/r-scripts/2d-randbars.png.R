#You need the cairo package from CRAN installed.
#If this is not possible, change svg("stats.svg") e.g. to jpeg("stats.jpg")
#Use with a 2-column stats.dat
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
png("2d-scatterplot.png",width=2500,height=4000)
plot(x=d[,1],
y=d[,2],
xlab="Value",
ylab="Count",
type="s",
col=heat.colors(length(d[,1])),
main="Binary file analysis results")
dev.off()
q()