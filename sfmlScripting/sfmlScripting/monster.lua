
function move(velocityY, moveCD, moved, lastMove)
	velocityY = velocityY - 128
	moveCD = 0
	moved = true
	lastMove = "N"
	return velocityY, moveCD, moved, lastMove
end