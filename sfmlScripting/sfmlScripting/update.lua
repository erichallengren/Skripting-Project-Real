function update(moveCD, sec)

	moveCD = moveCD + sec
	runMove = false
	-- �ndra h�r f�r att �ka eller s�nka farten p� spelet
	if moveCD >= 0.5 then
		runMove = true
	end

	return moveCD, runMove
end