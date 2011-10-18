# TODO: Add comment
# 
# Author: josue
###############################################################################
library(Biostrings)
library(seqLogo)
DNA <- DNAStringSet(c("CCCATTGTTCTC","TTTCTGGTTCTC","TCAATTGTTTAG","CTCATTGTTGTC","TCCATTGTTCTC","CCTATTGTTCTC","TCCATTGTTCGT","CCAATTGTTTTG"))
print(DNA)
pwm <- PWM(DNA)
print(pwm)
seqLogo(t(t(pwm) * 1/colSums(pwm)))



score2 <- function(s,DNA) # compute the frequence based in the sequence S
# s is the number of the sequence that will serve as reference	
{
	
	for (i in 1:7) {
		DNA2 <- DNAStringSet()
		DNA2 <- append (DNA2,DNAStringSet(c(DNA[[s]][i:(i + 3)])))
		for (j in 1:3){
			if (s != j){
				DNA2 <- append (DNA2,DNAStringSet(c(DNA[[j]][i:(i + 3)])))
			}
		}
		pwm_old <- PWM(DNA2)
		
		for (k in 2:7){
			DNA2 <- DNAStringSet()
			DNA2 <- append (DNA2,DNAStringSet(c(DNA[[s]][i:(i + 3)])))
			for (j in 1:3){
				if (s != j){
					DNA2 <- append (DNA2,DNAStringSet(c(DNA[[j]][k:(k + 3)])))
				}
			}
			pwm <- PWM(DNA2)
			print("old")
			print(pwm_old)
			max1 <- maxWeights(pwm_old)
			max2 <- maxWeights(pwm)
			for (w in 1:4) {
				if(max1[w] < max2[w]){
					next
				}
				print(max1)
			}
			print("new")
			print(pwm)
			
		}
	}	
}
