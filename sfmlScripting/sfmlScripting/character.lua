
function move(velocityX, velocityY, velocityXChange, velocityYChange, moveCDChange, movedChange, lastMoveChange, hasAttackedChange)
	
	velocityX = velocityX + velocityXChange	
	velocityY = velocityY + velocityYChange
	
	return velocityX, velocityY, moveCDChange, movedChange, lastMoveChange, hasAttackedChange
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
