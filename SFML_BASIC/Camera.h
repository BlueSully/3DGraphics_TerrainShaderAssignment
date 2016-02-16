#pragma comment(lib,"assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "GL/glu.h" 

//BUGS:
//	Rotating left/right and up/down do not interact correctly. After left/right rotation, up/down rotation will be skewed.

class Camera{
    static aiVector3D zero,xaxis,yaxis,zaxis;
public:
    aiVector3D position;
    aiVector3D forward;
    aiVector3D up;
 
    float forwardSpeed;
    float roationSpeed;
	float xangle = 1.57f;
	float yangle = 0;
     
    Camera():forwardSpeed(0.5f),roationSpeed(0.1f){}
 
	void Init(aiVector3D& p = zero, aiVector3D& f = zaxis, aiVector3D& u = yaxis){
        position=p;
		forward = f;
        up=u;
    }
 
	void Update(sf::Event e){//respond to keyboard events
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::D)){
                MoveLeftRight(1);
            }

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A)){
                MoveLeftRight(-1);
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
                TurnRightLeft(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Left)){
                TurnRightLeft(-1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Up)){
               TurnUpDown(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Down)){
               TurnUpDown(-1);
 
            }
	}
    void MoveLeftRight(int dir){ //Dir=+1=>Right, dir=-1=> Left
		position += (cross(forward,up).Normalize()*(forwardSpeed*dir));
    }

	void MoveUpDown(int dir){ //Dir=+1=>Right, dir=-1=> Left
		position += (up*(forwardSpeed*dir));
    }
 
    void MoveForwardBack(int dir){ //Dir=+1=>Forward, dir=-1=> Back
        position += (forward*(forwardSpeed*dir));
    }
 
    void TurnRightLeft(int dir){ //Dir=+1=>Right, dir=-1=> Left
		/*xangle += roationSpeed * dir;
		forward.x = cos(xangle);
		forward.z = sin(xangle);*/

		aiQuaternion q = aiQuaternion(up, dir*roationSpeed);
		forward = q.Rotate(forward);
		up = q.Rotate(up);
    }
         
    void TurnUpDown(int dir){ //Dir=+1=>Up, dir=-1=> Down
		/*yangle += roationSpeed * dir;
		forward.y = sin(yangle);
		forward.z = cos(yangle);
		up = cross(forward, aiVector3D(1, 0, 0));*/

		aiQuaternion q = aiQuaternion(cross(forward, up).Normalize(), -dir*roationSpeed);
		forward = q.Rotate(forward);
		up = q.Rotate(up);
    }
 
    void ViewingTransform(){
        gluLookAt(	position.x,position.y,position.z,// camera position
					position.x + forward.x, position.y + forward.y, position.z + forward.z, //look at this point
					up.x, up.y, up.z); //camera up
    }

	aiVector3D cross(aiVector3D x, aiVector3D y) {
		aiVector3D result(x.y * y.z - x.z * y.y, x.z * y.x - x.x * y.z, x.x * y.y - x.y * y.x);
		return result;
	}
 
};



//create some default vectors
aiVector3D Camera::zero(0.0f);
aiVector3D Camera::yaxis(0.0f,1.0f,0.0f);
aiVector3D Camera::zaxis(0.0f,0.0f,1.0f);
