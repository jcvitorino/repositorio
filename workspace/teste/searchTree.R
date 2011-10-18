# TODO: Add comment
# 
# Author: josue
###############################################################################

setClass("MWayTree", representation(m = "numeric", numberOfKeys = "numeric", key = "character", subtree = "character"))


setGeneric("searchClass",
		function(parameter, ...) {
			standardGeneric("searchClass")
		})

setMethod("searchClass",
		signature(),
		function(parameter) {
			
		})
