#pragma comment(lib,"assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "GL/glu.h" 



class Camera{
    static aiVector3D zero,xaxis,yaxis,zaxis;
public:
    aiVector3D position;
    aiVector3D forward;
	aiVector3D side;
    aiVector3D up;

	aiVector3D camFocus;

	aiMatrix3x3 mat;
 
    float forwardSpeed;
    float roationSpeed;
	float xangle = 0;
	float yangle = 0;
     
    Camera():forwardSpeed(0.5f),roationSpeed(0.5f){}
 
	void Init(aiVector3D& p = zero, aiVector3D& f = zaxis, aiVector3D& u = yaxis, aiVector3D& s = xaxis){
        position=p;
		forward = f;
		side=s;
        up=u;

		mat = aiMatrix3x3(1, 0, 0,
						  0, 1, 0,
						  0, 0, -1);

		camFocus = aiVector3D(position - forward);
    }
 
	void Update(sf::Event e){//respond to keyboard events
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::D)){
                MoveLeftRight(-1);
            }

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A)){
                MoveLeftRight(1);
            }
 
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::W)){
                MoveForwardBack(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::S)){
                MoveForwardBack(-1);
            }

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Q)){
                MoveUpDown(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::E)){
                MoveUpDown(-1);
            }
 
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Right)){
                TurnRightLeft(-1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Left)){
                TurnRightLeft(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Up)){
               TurnUpDown(-1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Down)){
               TurnUpDown(1);
 
            }

		//glRotatef(angle, 0, 1, 0);
	}
    void MoveLeftRight(int dir){ //Dir=+1=>Right, dir=-1=> Left
		position += (side*(forwardSpeed*dir));
    }

	void MoveUpDown(int dir){ //Dir=+1=>Right, dir=-1=> Left
		position += (up*(forwardSpeed*dir));
    }
 
    void MoveForwardBack(int dir){ //Dir=+1=>Forward, dir=-1=> Back
 
        position+=(forward*(forwardSpeed*dir));
    }
 
    void TurnRightLeft(int dir){ //Dir=+1=>Right, dir=-1=> Left
		xangle += roationSpeed * dir;
    }
         
    void TurnUpDown(int dir){ //Dir=+1=>Up, dir=-1=> Down
		yangle += roationSpeed * dir;
    }
 
    void ViewingTransform(){
        gluLookAt(	position.x,position.y,position.z,// camera position
					forward.x,forward.y,forward.z, //look at this point //TODO: BUG here!! what is it ??
					0,1,0); //camera up
    }
 
};

//create some default vectors
aiVector3D Camera::zero(0.0f);
aiVector3D Camera::xaxis(1.0f,0.0f,0.0f);
aiVector3D Camera::yaxis(0.0f,1.0f,0.0f);
aiVector3D Camera::zaxis(0.0f,0.0f,1.0f);
