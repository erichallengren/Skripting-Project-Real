
function move(velocityX, velocityY, moveCD, moved, lastMove, hasAttacked, velocityXChange, velocityYChange, moveCDChange, movedChange, lastMoveChange, hasAttackedChange)
	
	velocityX = velocityX + velocityXChange	
	velocityY = velocityY + velocityYChange
	moveCD = moveCDChange
	moved = movedChange
	lastMove = lastMoveChange
	hasAttacked = hasAttackedChange
	
	return velocityX, velocityY, moveCD, moved, lastMove, hasAttacked
end

function attack(moveCD, moved, attacking, hasAttacked, moveCDChange, movedChange, attackingChange, hasAttackedChange)

	moveCD = moveCDChange
	moved = movedChange
	attacking = attackingChange
	hasAttacked = hasAttackedChange

	return moveCD, moved, attacking, hasAttacked
end

function moveX(vx, amount)

	vx = vx + amount

	return vx
end

function moveY(vy, amount)

	vy = vy + amount

	return vy
end
