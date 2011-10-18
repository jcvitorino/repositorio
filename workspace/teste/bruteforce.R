library(Biostrings)
library(seqLogo)
#TODO fazer validações sobre o tamanho do  Olhar o FOR do bruteforce
score <- function(dnaSet) 
{
	resul <- 0 	
	len <- length(dnaSet)
	motifSize <- length(dnaSet[[1]])
	for(j in 1:motifSize){
		A <- C <- G <- T <- 0
		k <- j
		for(i in 1:len){
			l <- dnaSet[[i]][k:k]
			if(l == DNAString("A")){
				A <- A + 1
			}else if (l == DNAString("C")) {
				C <- C + 1
			}else if (l == DNAString("G")) {
				G <- G + 1
			}else if (l == DNAString("T")) {
				T <- T + 1 
			}			
		}
		posScore <- c(A,C,G,T)
		resul <- resul + max(posScore)
	}
	return(resul)
}

motifFind <- function(DNA,l) {
	bestMotif <- vector()
	bestScore <- 0
	len <- length(DNA)
	if (len != 5 ){
		print("Wrong size of DNA, at lest 2 and maximum 10")
	}else if (len == 3) {
		lenSeq <- length(DNA[[1]])
		for (i in 1:((lenSeq - l)+1)) {
			seq1 <- DNA[[1]][i:((i - 1)+l)]
			for (j in 1:((lenSeq - l)+1)) {
				seq2 <- DNA[[2]][j:((j - 1)+l)]
				for (k in 1:((lenSeq - l)+1)) {
					seq3 <- DNA[[3]][i:((k - 1)+l)]
					dnaSetTemp <- DNAStringSet()
					dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq1))
					dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq2))
					dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq3))
					countScore <- score(dnaSetTemp)
#			print(countScore)
					if(countScore > bestScore)
					{	
						bestScore <- countScore
						bestMotif[1] <- i
						bestMotif[2] <- j
						bestMotif[3] <- k
					}					
				}
			}
		}
	}else if (len == 5) {
		lenSeq <- length(DNA[[1]])
		for (i in 1:((lenSeq - l)+1)) {
			seq1 <- DNA[[1]][i:((i - 1)+l)]
			for (j in 1:((lenSeq - l)+1)) {
				seq2 <- DNA[[2]][j:((j - 1)+l)]
				for (k in 1:((lenSeq - l)+1)) {
					seq3 <- DNA[[3]][k:((k - 1)+l)]
					for (m in 1:((lenSeq - l)+1)) {
						seq4 <- DNA[[4]][m:((m - 1)+l)]
						for (x in 1:((lenSeq - l)+1)) {
							seq5 <- DNA[[5]][x:((x - 1)+l)]
							
							# Computation of the Score					
							dnaSetTemp <- DNAStringSet()
							dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq1))
							dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq2))
							dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq3))
							dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq4))
							dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq5))
							countScore <- score(dnaSetTemp)
				  #			print(countScore)
							if(countScore > bestScore)
							{	
								bestScore <- countScore
								bestMotif[1] <- i
								bestMotif[2] <- j
								bestMotif[3] <- k
								bestMotif[4] <- m
								bestMotif[5] <- x
							}
							# End of the computation of the score					
							
						}
					}	
				}
			}
		}
	}
	return(bestMotif)
}

bruteForce <- function(DNA,l)
{
	bestMotif <- vector()
	bestScore <- 0
	len <- length(DNA)
	lenSeq <- length(DNA[[1]])
	lenSeq2 <- length(DNA[[2]])
	for(i in 1:((lenSeq - l)+1)){
		seq1 <- DNA[[1]][i:((i -1)+l)]
#		print(seq1)
		for(j in 1:((lenSeq2 - l)+1)){
			seq2 <- DNA[[2]][j:((j - 1)+l)]
#			print(seq1)
			dnaSetTemp <- DNAStringSet()
			dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq1))
			dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq2))
			countScore <- score(dnaSetTemp)
#			print(countScore)
			if(countScore > bestScore)
			{	
				bestScore <- countScore
				bestMotif[1] <- i
				bestMotif[2] <- j
			}
			
		}
		
	}
	seq1 <- DNA[[1]][bestMotif[1]:((bestMotif[1] - 1)+l)]
	seq2 <- DNA[[2]][bestMotif[2]:((bestMotif[2] - 1)+l)]
	dnaSetTemp <- DNAStringSet()
	dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq1))
	dnaSetTemp <- append(dnaSetTemp,DNAStringSet(seq2))
#	print(dnaSetTemp)
	for (i in 1:(len-2))# for each sequences Si in S 
	{
		dnaSetTemp <- append(dnaSetTemp,DNAStringSet(""))
		for (j in 1:((lenSeq - l)+1))# (n-L)+1
		{
			seq <- DNA[[i + 2]][j:((j - 1)+l)]
			dnaSetTemp[[i + 2]] <- seq
			countScore <- score(dnaSetTemp)
			if(countScore > bestScore)
			{	
				bestScore <- countScore
				bestMotif[i + 2] <- j
			}		
		}
	}
	return(bestMotif)
}


medianString <- function() {
	i <- 1
	dna <-(c('a','a','a','a'))
	for (a in 1:4) {
		if(a == 1){
			dna[1] <- 'a'
		}else if (a == 2) {
			dna[1] <- 'c'
		}else if (a == 3) {
			dna[1] <- 'g'
		}else if (a == 4) {
			dna[1] <- 't'
		}		
		for (c in 1:4) {
			if(c == 1){
				dna[2] <- 'a'
			}else if (c == 2) {
				dna[2] <- 'c'
			}else if (c == 3) {
				dna[2] <- 'g'
			}else if (c == 4) {
				dna[2] <- 't'
			}			
			for (g in 1:4) {
				if(g == 1){
					dna[3] <- 'a'
				}else if (g == 2) {
					dna[3] <- 'c'
				}else if (g == 3) {
					dna[3] <- 'g'
				}else if (g == 4) {
					dna[3] <- 't'
				}
				for (t in 1:4) {
					if(t == 1){
					dna[4] <- 'a'
					}else if (t == 2) {
					dna[4] <- 'c'
					}else if (t == 3) {
					dna[4] <- 'g'
					}else if (t == 4) {
					dna[4] <- 't'
					}
					print(i)
					print(dna)
					i <- i + 1
				}
			}
		}
		
	}
	
}

consensoMotif <- function(bestMotif,DNA,motifSize){
	 len <- length(DNA)
	 dnaSetTemp <- DNAStringSet()
	 for (i in 1:len){
		 dnaSetTemp <- append(dnaSetTemp,DNAStringSet(DNA[[i]][bestMotif[i]:((bestMotif[i] - 1)+motifSize)]))
	 }
	 return(dnaSetTemp)
}

#DNA <- DNAStringSet(c("atccaGgtacTtagg", "ttgatCcAtacgtacac", "aaacgtTAgtgcacc","tcttacgtCcAtata","tcgttaCcgtacgGc"))
#DNA <- DNAStringSet(c("TTAGGTTT", "CCATAGGT", "ACGGAGGT", "ACGTAGGT", "CCGTAGGT"))
#bestMofif <- motifFind(DNA,4)
#dna <- consensoMotif(bestMofif,DNA,4)
#print(bestMofif)
#print(dna)
#pwm <- PWM(dna)
#seqLogo(t(t(pwm) * 1/colSums(pwm)))
medianString()