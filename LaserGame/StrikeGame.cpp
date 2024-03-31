#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <list>
#include <fstream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS


using namespace std;
using namespace sf;

class GunStand
{
public:
   const float _Width = 800.f;
   const float _Height = 100.f;
    GunStand()
    {
        _Stand.setFillColor(Color(0, 250, 250));
        _Stand.setSize(Vector2f(_Width,_Height));
        _Stand.setPosition(0.f, 700.f);
    }
    void draw(RenderWindow& window)
    {
        window.draw(_Stand);
    }
private:
    RectangleShape _Stand;

};
class Gun
{
public:
   
    GunStand _Stand;
    float _Width, _TWidth;
    float _Height, _THeight;
    float _GPos_X, _GPos_Y;
    float _TPos_X, _TPos_Y;
    float LaserPosEndX, LaserPosEndY;
    float len;
    float angle;
    RectangleShape _Gun;
    RectangleShape _Trunk;
    bool _isLaserActive = false;
    int _laserDuration;
    RectangleShape _Laser;
    float A;
    float B;
    float C;
    static bool intersec;
    Gun()
    {
        _Width = 80.f;
        _Height = 80.f;
        _TWidth = 4.f;
        _THeight = 70.f;
        _GPos_X = (_Stand._Width - _Width) / 2;
        _GPos_Y = 700.f -_Height;
        _Gun.setFillColor(Color(0, 200, 250));
        _Gun.setSize(Vector2f(_Width, _Height));
        _Gun.setPosition(_GPos_X, _GPos_Y);
        
        _TPos_X = _GPos_X - _TWidth / 2 + _Width * 0.5f;
        _TPos_Y = _GPos_Y + _Height/2;
        _Trunk.setFillColor(Color(100, 100, 250));
        _Trunk.setSize(Vector2f(_TWidth, _THeight));
        _Trunk.setOutlineThickness(1.f);
        _Trunk.setOutlineColor(sf::Color(255, 0, 255));
        _Trunk.setOrigin(_TWidth / 2, _THeight);
        _Trunk.setPosition(_TPos_X, _TPos_Y);
        

    }

    void updateTrunkRotation(Vector2f mousePosition)
    {
        Vector2f direction = mousePosition - _Trunk.getPosition();
        angle = atan2(direction.y, direction.x) * 180 / 3.14159265  + 90;
        if (angle > -90 && angle < 90)
        {
            _Trunk.setRotation(angle);
        }

       
    }
    void CreateLaser()
    {
        _Laser.setSize(Vector2f(2.f, 800.f));
        _Laser.setFillColor(Color::Red);
        _Laser.setOrigin(2 / 2, 800 + _THeight);
        _Laser.setPosition(_Trunk.getPosition().x, _Trunk.getPosition().y);
        _Laser.setRotation(_Trunk.getRotation());
       // cout << _Laser.getPosition().x ;
       // cout << "  " << _Laser.getPosition().y << endl;
    }
   
  
    void SetIsActiveLaser(bool value)
    {
        _isLaserActive = value;
    }
    void updateLaser(int diff)
    {
        if (_isLaserActive  == true)
        {
            
           
            _laserDuration -= diff;
            if (_laserDuration < 0)
            {
                _isLaserActive = false;
            }
           
        }
        
    }
    int Duration()
    {
      return _laserDuration = 50;
        
    }
   

    void draw(RenderWindow& window)
    {
        window.draw(_Gun);
        if (_isLaserActive == true)
        {
            window.draw(_Laser);
        }
        window.draw(_Trunk);
        
    }
  
   
}; 

random_device rd;
mt19937 gen(rd());
const float _SWidth = 30.f;
const float _SHeight = 30.f;
const float _CRadius = 15.f;
enum Direction
{
    DIR_LEFT, 
    DIR_RIGHT
};
bool Gun::intersec = false;

class Object 
{
public:
    RectangleShape square;
    CircleShape circle;
    //Gun gun;
    //float speed;
    //bool isActive = false;
    Direction direction;
    int type;
    Vector2f center;
    int PosX, PosY;
    static int cout;

    

    Object() 
    {
       
       // speed = 1.0f;
        //isActive = true;
        type = rd() % 2;
        
        if (type == 0)
        {
            square.setFillColor(Color::Yellow);
            square.setSize(Vector2f(_SWidth, _SHeight));
           
           // square.setPosition(PosX, PosY);
        }
        else
        {
            circle.setFillColor(Color::Blue);
            circle.setRadius(_CRadius);
            //circle.setPosition(PosX = rd() % 800, PosY = rd() % 480 + 20);
        }
        

    }
   
    void SetPosition(int x, int y)
    {
        if (type == 0)
        {
            square.setPosition(x, y);
        }
        else
        {
            circle.setPosition(x, y);
        }
    }
    Vector2f GetPosition()
    {
        if (type == 0)
        {
           return square.getPosition();
        }
        else
        {
           return circle.getPosition();
        }
    }
    void move(float x, float y)
    {
        if (type == 0)
        {
            square.move(x, y);
        }
        else
        {
            circle.move(x, y);
        }
    }

  
};
class List : Object
{
public:
    Vector2f GetCenterCircle(list<Object>::iterator it)
    {

        float centerX = it->GetPosition().x + _CRadius;
        float centerY = it->GetPosition().y + _CRadius;
        return center = Vector2f(centerX, centerY);

    }
    void CreateObjects()
    {
        objects.clear();
        for (int i = 0; i < 8; i++)
        {
            objects.emplace_back();
        }
    }
    void SpawnObject()
    {
        vector<pair<int, int>> occupiedPositionRanges;

        for (auto& o : objects)
        {

            PosY = rd() % 480 + 20;

            while (true)
            {
                bool positionOccupied = false;
                for (const auto& range : occupiedPositionRanges)
                {
                    if (PosY >= range.first && PosY <= range.second)
                    {

                        positionOccupied = true;
                        break;
                    }
                }

                if (!positionOccupied)
                {
                    break;
                }


                PosY = rd() % 480 + 20;
            }
            o.direction = (Direction)(rd() % 2);
            if (o.direction == DIR_RIGHT)
            {
                PosX = 0;
            }
            else
            {
                PosX = 770;
            }
            o.SetPosition(PosX, PosY);

            occupiedPositionRanges.push_back({ PosY - 35.f, PosY + 35.f });
        }
    }
  
    void Intersection(Gun& gun)
    {
        for (auto it = objects.begin(); it != objects.end();)
        {
            gun.LaserPosEndX = gun._Laser.getPosition().x + 800.f * cos((gun.angle + 90) * 3.14159265 / 180);

            gun.LaserPosEndY = gun._Laser.getPosition().y + 800.f * sin((gun.angle + 90) * 3.14159265 / 180);

            gun.A = gun.LaserPosEndY - gun._Laser.getPosition().y;

            gun.B = gun._Laser.getPosition().x - gun.LaserPosEndX;

            gun.C = gun.LaserPosEndX * gun._Laser.getPosition().y - gun._Laser.getPosition().x * gun.LaserPosEndY;

            if (it->type == 1)
            {
                float distance = abs(gun.A * GetCenterCircle(it).x + gun.B * GetCenterCircle(it).y + gun.C) / sqrt(gun.A * gun.A + gun.B * gun.B);
                if (distance <= _CRadius)
                {

                    Gun::intersec = true;
                    cout++;
                   
                }
                else
                {
                    Gun::intersec = false;
                   
                }
                if (Gun::intersec)
                {
                    it = objects.erase(it);
                }
                else
                {
                    it++;
                }
            }
            else
            {
                
                

                if ((gun.A * it->GetPosition().x + gun.B * it->GetPosition().y + gun.C) * (gun.A * (it->GetPosition().x + _SWidth) + gun.B * it->GetPosition().y + gun.C) <= 0 ||
                    (gun.A * (it->GetPosition().x + _SWidth) + gun.B * it->GetPosition().y  + gun.C) * (gun.A * (it->GetPosition().x + _SWidth) + gun.B * (it->GetPosition().y + _SHeight) + gun.C) <= 0 ||
                    (gun.A * (it->GetPosition().x + _SWidth) + gun.B * (it->GetPosition().y + _SHeight) + gun.C) * (gun.A * it->GetPosition().x + gun.B * (it->GetPosition().y + _SHeight) + gun.C) <= 0 ||
                    (gun.A * it->GetPosition().x + gun.B * (it->GetPosition().y + _SHeight) + gun.C) * (gun.A * it->GetPosition().x + gun.B * it->GetPosition().y + gun.C) <= 0)
                {
                    Gun::intersec = true;
                    cout++;
                }
                else
                {
                    Gun::intersec = false;
                }
                if (Gun::intersec)
                {
                    it = objects.erase(it);
                   
                }
                else
                {
                    it++;
                }
                
            }
        }
    }
    void MoveObjects()
    {
        for (auto it = objects.begin(); it != objects.end();)
        {
            if (it->GetPosition().x < 0 || it->GetPosition().x > 770)
            {
                it = objects.erase(it);
            }
            else
            {
                if (it->direction == DIR_RIGHT)
                {
                    it->move(0.02f, 0.f);
                }
                else
                {
                    it->move(-0.02f, 0.f);
                }
                ++it;
            }
        }
    }
    bool isListEmpty()
    {
        if (objects.empty())
               return true;
    }
    void drawObjects(RenderWindow& window)
    {
        for (auto& o : objects) {

            if (o.type == 0) {
                window.draw(o.square);
            }
            else if (o.type == 1) {
                window.draw(o.circle);
            }

        }
    }
   
   
private:
    list<Object> objects;
   
};
int Object::cout = 0;
Font font;
class Score
{
public:
    
    Score()
    {
        std::string FileName = "D:\\изучение c++\\StrikeGame\\x64\\Debug\\font\\ofont.ru_Europe.ttf";
        if (!font.loadFromFile(FileName))
        { 
            cout << "error" << endl;
        }
      
       ScoreText.setFont(font);
       ScoreText.setString(L"Score: 0");
       ScoreText.setCharacterSize(18);
       ScoreText.setFillColor(Color::Green);
       ScoreText.setPosition(600.f - ScoreText.getGlobalBounds().width, 5.f);

       OpenRecord();
       Record.setFont(font);
       Record.setString(L"Record Score: " + ScoreRecord);
       Record.setCharacterSize(18);
       Record.setPosition(200.f, 5.f);
       
    }
   
    void ScoreChage()
    {
        if (Object::cout > 0)
        {
            score += Object::cout;
            ScoreText.setString(L"Score: " + to_string(score));
            ScoreText.setFillColor(Color::Green);
            Object::cout = 0;           
            //Gun::intersec = false;
        }
        else 
        {
            
            score -= 3;
            if (score < 0)
                score = 0;
            ScoreText.setString(L"Score: " + to_string(score));
            ScoreText.setFillColor(Color::Red);
            
              
        }
        
       // cout << Gun::intersec << endl;

    }
    void UpdateColor(int diff)
    {
        if (Object::cout == 0)
        {
          
            Timer -= diff;
            if (Timer < 0)
            {
                ScoreText.setFillColor(Color::Green);
                Timer = 1500;
            }
            
            
            
           
        }
    }
    void SaveRecord()
    {
        record = stoi(ScoreRecord);
        ofstream file;
        file.open("record.txt");
        if (record < score)
            record = score;       
        file << record;
        file.close();
    }
    void OpenRecord()
    {
        ifstream file;
        file.open("record.txt");
        while (getline(file, ScoreRecord)) { }
        file.close();
        
       
    }
    void drawScore(RenderWindow& window)
    {
       window.draw(ScoreText);
       window.draw(Record);
    }
private:
    int score = 0;
    Text ScoreText;
    int Timer = 1500;
    Text Record;
    string ScoreRecord;
    int record = 0;
 
   
};
int main()
{   
    setlocale(LC_ALL, "ru");
    RenderWindow window(VideoMode(800, 800), "Skeet Shooting");
   
    Gun _Gun;
    GunStand _GunStand;
    List _List;
    Score _Score;
   


    Clock clock;
    Time time = clock.getElapsedTime();
   
   
   
  
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseMoved)
            {
                _Gun.updateTrunkRotation(Vector2f(event.mouseMove.x, event.mouseMove.y));
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
            {
                _Gun.CreateLaser();
                _Gun.SetIsActiveLaser(true);
                _Gun.Duration();
                 _List.Intersection(_Gun);
                 _Score.ScoreChage();
            }

        }

        Time time2 = clock.getElapsedTime();
        int diff = time2.asMilliseconds() - time.asMilliseconds();
        time = time2;


        _Gun.updateLaser(diff);
        _Score.UpdateColor(diff);
        //cout << _Gun.GetPosLaserEnd() << endl;
        //cout << _Gun.Lenght() << endl;
       
        if (_List.isListEmpty())
        {
            _List.CreateObjects();
            _List.SpawnObject();
           
        }
        
        _List.MoveObjects();
           
        
        

        window.clear();
        _Score.drawScore(window);
        _GunStand.draw(window);
        _Gun.draw(window);
        _List.drawObjects(window);
        window.display();

    }
    _Score.SaveRecord();
   
    return 0;
}
    

