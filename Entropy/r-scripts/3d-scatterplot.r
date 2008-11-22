#Needs scatterplot 3d
#Use with a 3-column stats.dat
library ("scatterplot3d")
d <- read.csv(file="stats.dat", header=TRUE,sep=",")
png("3d-scatterplot.png",width=2500,height=2500)
par(oma=c(5,5,5,5))
scatterplot3d(z=d$Count, y=d$Number, x=d$Block, highlight.3d=TRUE, col.axis="blue",
      col.grid="lightblue", main="Binary file analysis", pch=16,
      xlab="Block number",ylab="Number",zlab="Count",
      cex.lab=4,cex.axis=3,grid=TRUE,)
dev.off()
q()
 