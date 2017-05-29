library(ggplot2)
library(plyr)
library(extrafont)

loadfonts()

data1 <- read.table("avx_iterative_unmerged.txt")
data1$Method <- "AVX"
data2 <- read.table("naive_iterative_unmerged.txt")
data2$Method <- "Naive"
data3 <- read.table("avx_iterative_merged.txt")
data3$Method <- "Merged"
data <- rbind(data1, data2, data3)
data <- rename(data, c("V1"="Size", "V2"="Time"))
#data <- data[data$Size <= 10,]
ggplot(data, aes(x=Size, y=Time, colour=Method)) +
  geom_line(size=2.0) +
  scale_x_continuous(breaks=c(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27)) +
  scale_y_log10(breaks=c(1e-9, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1)) +
  theme_bw() +
  theme(text = element_text(size = 18, family="Open Sans Semibold"))
ggsave("plots.png")