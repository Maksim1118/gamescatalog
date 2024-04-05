#include <SFML/Graphics.hpp>
#include <random>
#include <list>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

class Stand
{
public:
    Stand()
    {
      
        
        stand.setPointCount(11);

        stand.setPoint(0, Vector2f(0.f, 800.f));
        stand.setPoint(1, Vector2f(300.f, 800.f));
        stand.setPoint(2, Vector2f(550.f, 700.f));
        stand.setPoint(3, Vector2f(650.f, 750.f));
        stand.setPoint(4, Vector2f(800.f, 750.f));
        stand.setPoint(5, Vector2f(950.f, 680.f));
        stand.setPoint(6, Vector2f(1150.f, 680.f));
        stand.setPoint(7, Vector2f(1350.f, 800.f));
        stand.setPoint(8, Vector2f(1600.f, 800.f));
        stand.setPoint(9, Vector2f(1600.f, 900.f));
        stand.setPoint(10, Vector2f(0.f, 900.f));

        stand.setFillColor(Color::Cyan);
    }
    void draw(RenderWindow& window)
    {

        window.draw(stand);
    }
    static ConvexShape stand;
private:
    
    
};

class Gun
{
public:
    Gun()
    {
        StandGun.setSize(Vector2f(70.f, 70.f));
        StandGun.setPosition(100.f, 800.f - StandGun.getGlobalBounds().height);
        StandGun.setFillColor(Color(150, 150, 150));

        _Gun.setSize(Vector2f(16.f, 60.f));
        GunPosX = 100.f  + StandGun.getGlobalBounds().width / 2.f;
        GunPosY = 800.f - StandGun.getGlobalBounds().height / 2.f;
        _Gun.setPosition(GunPosX, GunPosY);
        _Gun.setFillColor(Color(170, 170, 255));
        _Gun.setOrigin(_Gun.getSize().x / 2.f, _Gun.getSize().y);
        
    }
    float  TrunkRotation(Vector2f musePos)
    {
        Vector2f dir = musePos - _Gun.getPosition();
        angle = atan2(dir.y, dir.x) * 180 / 3.14159265 + 90.f;
        if (angle > 0 && angle < 90)
        {
            _Gun.setRotation(angle);
            return angle;
        }
        
    }
    void draw(RenderWindow& window)
    {
        window.draw(StandGun);
        window.draw(_Gun);
    }
protected:
    RectangleShape StandGun;
    RectangleShape _Gun;
    float GunPosX;
    float GunPosY;
    float angle;

};
random_device random;
mt19937 generate(random());

class Shapes
{
public:
    virtual void draw(RenderWindow& window) = 0;
    virtual void SetPosition(float x, float y) = 0;
    virtual float GetHeight() const = 0;
    virtual void SetOrigin(float x, float y) = 0;
    virtual void SetRotation(float angle) = 0;
    virtual Vector2f GetPos() const = 0;
};
class Ball: public Shapes
{
public:
    Ball()
    {
        shape.setRadius(20.f);
        shape.setFillColor(Color(255, 225, 255));
       // shape.setPosition(random() % 1250 + 300, random() % 120 + 640);
    }
    void SetPosition(float x, float y)
    {
        shape.setPosition(x, y);
    }
    float  GetHeight() const
    {
        return shape.getGlobalBounds().height;
    }
    void SetOrigin(float x, float y)
    {
        shape.setOrigin(x, y);
    }
    void SetRotation(float angle)
    {
        shape.setRotation(angle);
       
    }
    Vector2f GetPos() const
    {
        return  shape.getPosition();
    }
    void draw(RenderWindow& window)override
    {
        window.draw(shape);
    }
private:
    CircleShape shape;
};
class Cube: public Shapes
{
public:
    Cube()
    {
        shape.setSize(Vector2f(40.f, 40.f));
        // shape.setPosition(random() % 1250 + 300, random() % 120 + 640);
        shape.setFillColor(Color::Yellow);
    }
    void SetPosition(float x, float y)
    {
        shape.setPosition(x, y);
    }
    float GetHeight() const
    {
        return shape.getGlobalBounds().height;
    }
    void SetOrigin(float x, float y)
    {
        shape.setOrigin(x, y);
    }
    void SetRotation(float angle)
    {
        shape.setRotation(angle);
    }
    Vector2f GetPos() const
    {
        return  shape.getPosition();
    }
    void draw(RenderWindow& window)
    {
        window.draw(shape);
    }
private:
    RectangleShape shape;
};
ConvexShape Stand::stand;
class Objects
{
   
public:
    
    void CreateObjects()
    {
        objects.clear();
        for (int i = 0; i < 8; i++)
        {
            Choose = random() % 2;
            if (Choose == 0)
            {
                objects.push_back(make_unique<Ball>());
            }
            else
            {
                objects.push_back(make_unique<Cube>());
            }
        }

    }
    /*float PosToLine(const Vector2f& p, const Vector2f& l1, const Vector2f& l2)
    {
        /*float A = p.x - l1.x;
        float B = p.y - l1.y;
        float C = l2.x - l1.x;
        float D = l2.y - l1.y;

        float dot = A * C + B * D;
        float len_sq = C * C + D * D;
        float param = dot / len_sq;

        float x_onLine, y_onLine;
        if (param < 0)
        {
            x_onLine = l1.x;
            y_onLine = l1.y;
        }
        else if (param > 1)
        {
            x_onLine = l2.x;
            y_onLine = l2.y;
        }
        else
        {
            x_onLine = l1.x + param * C;
            y_onLine = l1.y + param * D;
        }
        return sqrt((p.x - x_onLine) * (p.x - x_onLine) + (p.y - y_onLine) * (p.y - y_onLine));
       // return fabs(A * p.x + B * p.y + C) / sqrt(A * A + B * B);
        float A = l2.y - l1.y;
        float B = l1.x - l2.x;
        float C = l2.x * l1.y - l1.x * l2.y;
        
        //Pos.y = (-A * p.x - C) / B;
        
        return abs(A * p.x + B * p.y + C);
   }*/
    
    /*void SpawnObjects()
    {
        for (auto& o: objects)
        {
            Vector2f newPos;
            float newAngle;
            int PosX;
            bool intersec = true;
            while (intersec)
            {
                PosX = random() % 1250 + 300;
                //newPos = Vector2f(random() % 1250 + 300, random() % 800);
                intersec = false;
               
                float minDist = numeric_limits<float>::max();

                for (size_t i = 0; i < Stand::stand.getPointCount(); i++)
                {
                    float dist = DistancePointToLine(newPos, Stand::stand.getPoint(i), Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()));
                    minDist = min(minDist, dist);
                }
                if (minDist != 40.f)
                {
                    intersec = true;
                    continue;
                }               
                for (auto& other : objects)
                {
                    if (o != other)
                    {
                        const Vector2f Pos1 = newPos;
                        const Vector2f Pos2 = other->GetPos();
                        if (sqrt((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y)) < 45.f)
                        {
                            intersec = true;
                            break;
                        }
                    }
                }
            }
            float  dx = Stand::stand.getPoint(1).x - Stand::stand.getPoint(0).x;
            float dy = Stand::stand.getPoint(1).y - Stand::stand.getPoint(0).y;
            newAngle = atan2(dy, dx) * 180 / 3.14159;
            o->SetPosition(newPos.x, newPos.y);
            o->SetRotation(newAngle);
           
        }
    }*/
    void SpawnObjects()
    {
        for (auto& o : objects)
        {
            bool cycle = true;
            float newAngle;
            while (cycle)
            {
                Pos.x = random() % 1250 + 302;
                bool intersec = false;
                //Pos.x = 900;
                for (size_t i = 0;  cycle && i < Stand::stand.getPointCount(); i++)
                {
                   
                    
                    float x1 = Stand::stand.getPoint(i).x;
                    float y1 = Stand::stand.getPoint(i).y;
                    float x2 = Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()).x;
                    float y2 = Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()).y;
                    if ((int)Pos.x > (int)x1 + 5 && Pos.x < (int)x2 - 45)
                    {
                        if (x2 - x1 != 0)
                        {
                            float y = y1 + ((y2 - y1) / (x2 - x1)) * (Pos.x - x1);
                            Pos.y = (int)y;
                            for (auto& other : objects)
                            {
                                if (o != other) 
                                {
                                    const Vector2f Pos1 = Pos;
                                    const Vector2f Pos2 = other->GetPos();
                                    if (sqrt((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y)) < 45.f)
                                    {
                                        intersec = true;
                                        break;
                                    }
                                    
                                }   
                            }
                            if (!intersec)
                            {
                                cycle = false;

                                float  dx = (int)Stand::stand.getPoint((i + 1) % (int)Stand::stand.getPointCount()).x - (int)Stand::stand.getPoint(i).x;
                                float dy = (int)Stand::stand.getPoint((i + 1) % (int)Stand::stand.getPointCount()).y - (int)Stand::stand.getPoint(i).y;
                                newAngle = atan2(dy, dx) * 180 / 3.14159;


                                o->SetPosition(Pos.x, Pos.y);
                                o->SetOrigin(0.f, 40.f);
                                o->SetRotation(newAngle);
                                break;
                            }
                        }
                    }
                                          
                }
               
            }
            

           /* stand.setPoint(0, Vector2f(0.f, 800.f));
        stand.setPoint(1, Vector2f(300.f, 800.f));
        stand.setPoint(2, Vector2f(550.f, 700.f));
        stand.setPoint(3, Vector2f(650.f, 750.f));
        stand.setPoint(4, Vector2f(800.f, 750.f));
        stand.setPoint(5, Vector2f(950.f, 680.f));
        stand.setPoint(6, Vector2f(1150.f, 680.f));
        stand.setPoint(7, Vector2f(1350.f, 800.f));
        stand.setPoint(8, Vector2f(1600.f, 800.f));
        stand.setPoint(9, Vector2f(1600.f, 900.f));
        stand.setPoint(10, Vector2f(0.f, 900.f));*/

            /*int dir = (int)Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()).y - (int)Stand::stand.getPoint(i).y;
                       if (dir == 0.f)
                       {
                           Pos.y = (int)Stand::stand.getPoint(i).y;
                       }
                       else if (dir < 0.f)
                       {
                           dir = (int)Stand::stand.getPoint(i).y - (int)Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()).y;
                           Pos.y = random() % dir + (int)Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()).y;
                       }
                       else
                       {
                           Pos.y = random() % dir + (int)Stand::stand.getPoint(i).y;
                       }
                       int distance = PosToLine(Pos, Stand::stand.getPoint(i), Stand::stand.getPoint((i + 1) % Stand::stand.getPointCount()));
                       if (distance == 0)
                       {
                           cycle = false;
                           o->SetPosition(Pos.x, Pos.y - 40.f);
                           break;
                       }*/
        }
    }
    
    void drawObjects(RenderWindow& window)
    {
        for (auto& o : objects)
        {
            o->draw(window);
        }
    }
private:
    int Choose;
    list<unique_ptr<Shapes>> objects;
    Vector2f Pos;
};
class Patrons : public Gun
{
public:

    int index = 0;
    vector<Patrons> patrons;
    Patrons()
    {
      
        shape.setRadius(5);
        shape.setFillColor(Color::Green);
        
    }
    void CreatePatrons()
    {
        patrons.clear();
        for (int i = 0; i < 10; i++)
        {
            patrons.emplace_back();
        }
    }
    void Spawn(float angle)
    {
        float angleRad = angle * (3.14159 / 180);
        float GunX = _Gun.getPosition().x  + _Gun.getSize().y * sin(angleRad);
        float GunY = _Gun.getPosition().y - _Gun.getSize().y * cos(angleRad);
       
        patrons[index].shape.setPosition(GunX - 5, GunY - 5);
    }
  
    void Move()
    {
        patrons[index].shape.move(0.0005f, 0.0005f);
    }
    void draw(RenderWindow& window)
    {
        for (int i = 0; i <= index; i++)
        {
            window.draw(patrons[i].shape);
        }
       
    }
private:
    CircleShape shape;
    
};
int main()
{

    ContextSettings settings;
    settings.antialiasingLevel =  8;

    RenderWindow window(VideoMode(1600, 900), "AngryGame", Style::Default, settings);

   
    Stand _stand;
    Gun gun;
    Objects _objects;
    Patrons _patrons;
    _objects.CreateObjects();
    _objects.SpawnObjects();
    _patrons.CreatePatrons();
    bool ButtonPressed = false;
    float SaveAngle;
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
         
            if (event.type == Event::MouseMoved)
            {
                SaveAngle = gun.TrunkRotation(Vector2f(event.mouseMove.x, event.mouseMove.y));
                if (SaveAngle >= 0 && SaveAngle <= 90)
                {
                    if (_patrons.index < _patrons.patrons.size())
                    {
                        _patrons.Spawn(SaveAngle);

                       
                        
                    }

                }
                
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
            {
                ButtonPressed = true;
                //_patrons.index++;
               
            }
            if (event.type == Event::Closed)
                window.close();
            
        }
        if(ButtonPressed)
            _patrons.Move();
        //_patrons.SpawnAndMove();
       //_patrons.Move();
        //_patrons.PatronRotate();
        window.clear();
        
        
        _stand.draw(window);
        _objects.drawObjects(window);
       //if (ButtonPressed)
        _patrons.draw(window);
        gun.draw(window);
        window.display();
       
        
    }

    return 0;
}