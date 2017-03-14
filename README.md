<<<<<<< HEAD
Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)
=======
# othello
>>>>>>> 5566da5932fb9ddc8588803ed26a5d40de3f9af7

Max coded the AI that made random moves, which satisfied the first 5 points of part 1's assignment as it was a working AI. Dana coded the AI that could beat simpleplayer most of the time by making the AI move into a corner if possible and not move next to a corner if possible. 

First, we tried to have the AI move to any edge possible if a corner was not possible, but this AI lost to SimplePlayer more than 50% of the time. We then implemented minimax on our corner scoring system and it was successful, beating simpleplayer by wider margins. However it still could not beat better player.
