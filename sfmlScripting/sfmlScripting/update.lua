function update(moveCD, sec)

	moveCD = moveCD + sec
	runMove = false
	-- ändra här för att öka eller sänka farten på spelet
	if moveCD >= 0.5 then
		runMove = true
	end

	return moveCD, runMove
end