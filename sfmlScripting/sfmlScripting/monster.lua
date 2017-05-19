

function moveX(vx, amount)

	vx = vx + amount

	return vx
end

function moveY(vy, amount)

	vy = vy + amount

	return vy
end

function moveOld(vx, vy, rayx, rayy, mn)
	if rayx == 0 && rayy != 0 then
		if rayy >= 0 then
			vy += 128 
		end
		if rayy < 0 then
			vy -= 128
		end
	end
	if rayy == 0 && rayx != 0 then
		if rayx >= 0 then
			vx += 128 
		end
		if rayx < 0 then
			vx -= 128
		end
	end
	if rayx != 0 && rayy != 0 then
		if mn == 1 then
			if rx >= 0 then
				vx += 128 
			end
			if rx < 0 then
				vx -= 128
			end
		end
		if mn != 1 then
			if ry >= 0 then
				vy += 128 
			end
			if ry < 0 then
				vy -= 128
			end
		end
	end

	return vx, vy, rayx, rayy, lastMove
end