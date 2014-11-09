chess :	 main.o Board.o StatusBoard.o Cell.o King.o Laser.o BlockMirror.o TriMirror.o HyperMirror.o AttackLaser.o BeamSplitter.o Mirror.o Unit.o StunLaser.o
	g++ -o chess main.o Board.o StatusBoard.o Cell.o King.o Laser.o BlockMirror.o TriMirror.o HyperMirror.o AttackLaser.o BeamSplitter.o Mirror.o Unit.o StunLaser.o

main.o : main.cpp Board.h
	g++ -c main.cpp

Board.o : Board.cpp Board.h Global.h StatusBoard.h Cell.h Unit.h King.h Laser.h
	g++ -c Board.cpp

StatusBoard.o : StatusBoard.cpp StatusBoard.h Cell.h
	g++ -c StatusBoard.cpp

Cell.o :	Cell.cpp Cell.h Global.h Unit.h King.h AttackLaser.h StatusBoard.h BlockMirror.h TriMirror.h HyperMirror.h BeamSplitter.h
	g++ -c Cell.cpp

King.o : King.cpp King.h Unit.h
	g++ -c King.cpp

Laser.o : Laser.cpp Laser.h Unit.h
	g++ -c Laser.cpp

BlockMirror.o : BlockMirror.cpp BlockMirror.h Mirror.h
	g++ -c BlockMirror.cpp

TriMirror.o : TriMirror.cpp TriMirror.h Mirror.h
	g++ -c TriMirror.cpp

HyperMirror.o : HyperMirror.cpp HyperMirror.h Mirror.h
	g++ -c HyperMirror.cpp

AttackLaser.o : AttackLaser.cpp AttackLaser.h Laser.h
	g++ -c AttackLaser.cpp

BeamSplitter.o : BeamSplitter.cpp BeamSplitter.h Mirror.h
	g++ -c BeamSplitter.cpp

Mirror.o : Mirror.cpp Mirror.h Unit.h
	g++ -c Mirror.cpp

Unit.o : Unit.cpp Unit.h Global.h
	g++ -c Unit.cpp

StunLaser.o : StunLaser.cpp StunLaser.h Laser.h
	g++ -c StunLaser.cpp

clean :
	rm *.o
	rm chess
