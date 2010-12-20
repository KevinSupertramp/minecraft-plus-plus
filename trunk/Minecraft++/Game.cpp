#include "Global.h"

bool Game::Active;
double fps = 0;
double tdelta = 0;
double delta = 0;
uint64_t ticks = 0;

bool Game::Init() {
	InitBlocks();
	Window.Create(sf::VideoMode(800,600,32),"Minecraft++",sf::Style::Close|sf::Style::Titlebar,sf::ContextSettings(24,0,0,3,3));
	Window.ShowMouseCursor(false);
	//Window.SetFramerateLimit(30);
	InitGraphics();
	Window.SetActive();
	Active = true;
	boost::thread thread(ChunkUpdateThread);
	srand(clock());
	return true;
}
bool Game::Loop() {
	//Event handling
	sf::Event e;
	while(Window.GetEvent(e)){
		switch(e.Type){
		case sf::Event::Closed:
			Window.Close();
			break;
		case sf::Event::KeyPressed:
			switch(e.Key.Code){
			case sf::Key::Escape:
				Window.Close();
				break;
			}
		case sf::Event::GainedFocus:
			Active = true;
			break;
		case sf::Event::LostFocus:
			Active = false;
			break;
		}
	}
	player.Step();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(double)Window.GetWidth()/Window.GetHeight(),0.1,1000);
	gluLookAt(0,0,0,ldx(1,player.rot.d)*ldx(1,player.rot.p),ldy(1,player.rot.d)*ldx(1,player.rot.p),ldy(1,player.rot.p),0,0,-1);
	glTranslated(-player.pos.x,-player.pos.y,-player.pos.z);
	glMatrixMode(GL_MODELVIEW);
	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	//Draw everything
	int range = 4;
	glBindTexture(GL_TEXTURE_3D,TEX);
	for(int64_t a=0;a<=range;a++){
		for(int64_t b=0;b<=range;b++){
			for(int64_t c=0;c<=range;c++){
				GetChunk(player.pos.cx+a,player.pos.cy+b,player.pos.cz+c)->Draw();
				if(a!=0){GetChunk(player.pos.cx-a,player.pos.cy+b,player.pos.cz+c)->Draw();}
				if(b!=0){GetChunk(player.pos.cx+a,player.pos.cy-b,player.pos.cz+c)->Draw();}
				if(c!=0){GetChunk(player.pos.cx+a,player.pos.cy+b,player.pos.cz-c)->Draw();}
				if(a!=0 && b!=0){GetChunk(player.pos.cx-a,player.pos.cy-b,player.pos.cz+c)->Draw();}
				if(b!=0 && c!=0){GetChunk(player.pos.cx+a,player.pos.cy-b,player.pos.cz-c)->Draw();}
				if(c!=0 && a!=0){GetChunk(player.pos.cx-a,player.pos.cy+b,player.pos.cz-c)->Draw();}
				if(a!=0 && b!=0 && c!=0){GetChunk(player.pos.cx-a,player.pos.cy-b,player.pos.cz-c)->Draw();}
			}
		}
	}
	//Display the screen
	Window.Display();
	fps = fps*0.8+0.2/Window.GetFrameTime();
	tdelta += Window.GetFrameTime();
	delta = Window.GetFrameTime();
	ticks++;
	if(ticks%10==0){
		cout << fps << endl;
	}
	return Window.IsOpened();
}
void Game::Unload() {

}