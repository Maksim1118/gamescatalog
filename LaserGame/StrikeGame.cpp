#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <list>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
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
        _Stand.setSize(Vector2f(_Width, _Height));
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
    float _Width, _Height;
    float _TrunkWidth, _TrunkHeight;
    float _GunPosX, _GunPosY;
    float _TrunkPosX, _TrunkPosY;
    float _LaserPosEndX, _LaserPosEndY;
    float _Len;
    float _Angle;
    RectangleShape _Gun;
    RectangleShape _Trunk;
    bool _IsLaserActive = false;
    int _LaserDuration;
    RectangleShape _Laser;
    // формула прямой Ax + By +  C = 0
    float _A;
    float _B;
    float _C;
    static bool _Intersec;

    Gun()
    {
        _Width = 80.f;
        _Height = 80.f;
        _TrunkWidth = 4.f;
        _TrunkHeight = 70.f;
        _GunPosX = (_Width - _Width) / 2;
        _GunPosY = 700.f - _Height;
        _Gun.setFillColor(Color(0, 200, 250));
        _Gun.setSize(Vector2f(_Width, _Height));
        _Gun.setPosition(_GunPosX, _GunPosY);

        _TrunkPosX = _GunPosX - _TrunkWidth / 2 + _Width * 0.5f;
        _TrunkPosY = _GunPosY + _Height / 2;
        _Trunk.setFillColor(Color(100, 100, 250));
        _Trunk.setSize(Vector2f(_TrunkWidth, _TrunkHeight));
        _Trunk.setOutlineThickness(1.f);
        _Trunk.setOutlineColor(sf::Color(255, 0, 255));
        _Trunk.setOrigin(_TrunkWidth / 2, _TrunkHeight);
        _Trunk.setPosition(_TrunkPosX, _TrunkPosY);
    }

    void updateTrunkRotation(Vector2f mousePosition)
    {
        Vector2f _Direction = mousePosition - _Trunk.getPosition();
        _Angle = atan2(_Direction.y, _Direction.x) * 180 / 3.14159265 + 90;
        if (_Angle > -90 && _Angle < 90)
        {
            _Trunk.setRotation(_Angle);
        }
    }

    void createLaser()
    {
        _Laser.setSize(Vector2f(2.f, 800.f));
        _Laser.setFillColor(Color::Red);
        _Laser.setOrigin(2 / 2, 800 + _TrunkHeight);
        _Laser.setPosition(_Trunk.getPosition().x, _Trunk.getPosition().y);
        _Laser.setRotation(_Trunk.getRotation());
    }

    void setIsActiveLaser(bool value)
    {
        _IsLaserActive = value;
    }

    void updateLaser(int diff)
    {
        if (_IsLaserActive == true)
        {
            _LaserDuration -= diff;
            if (_LaserDuration < 0)
            {
                _IsLaserActive = false;
            }
        }
    }

    int duration()
    {
        return _LaserDuration = 50;

    }

    void draw(RenderWindow& window)
    {
        window.draw(_Gun);
        if (_IsLaserActive == true)
        {
            window.draw(_Laser);
        }
        window.draw(_Trunk);
    }
};

random_device rd;
mt19937 gen(rd());
bool Gun::_Intersec = false;

const float squareWidth = 30.f;
const float squareHeight = 30.f;
const float circleRadius = 15.f;
enum Direction
{
    DIR_LEFT,
    DIR_RIGHT
};
class Object
{
public:

    RectangleShape _Square;
    CircleShape _Circle;
    Direction _Direction;
    int _TypeObj;
    Vector2f _Center;
    int _PosX, _PosY;
    static int _Count;

    Object()
    {
        _TypeObj = rd() % 2;
        if (_TypeObj == 0)
        {
            _Square.setFillColor(Color::Yellow);
            _Square.setSize(Vector2f(squareWidth, squareHeight));
        }
        else
        {
            _Circle.setFillColor(Color::Blue);
            _Circle.setRadius(circleRadius);
        }
    }

    void setPosition(int x, int y)
    {
        if (_TypeObj == 0)
        {
            _Square.setPosition(x, y);
        }
        else
        {
            _Circle.setPosition(x, y);
        }
    }

    Vector2f getPosition() const
    {
        if (_TypeObj == 0)
        {
            return _Square.getPosition();
        }
        else
        {
            return _Circle.getPosition();
        }
    }

    void move(float x, float y)
    {
        if (_TypeObj == 0)
        {
            _Square.move(x, y);
        }
        else
        {
            _Circle.move(x, y);
        }
    }
};

class List : Object
{
public:

    Vector2f getCenterCircle(list<Object>::iterator it)
    {
        float centerX = it->getPosition().x + circleRadius;
        float centerY = it->getPosition().y + circleRadius;
        return _Center = Vector2f(centerX, centerY);
    }
    void createObjects()
    {
        _Objects.clear();
        for (int i = 0; i < 8; i++)
        {
            _Objects.emplace_back();
        }
    }

    void spawnObject()
    {
        vector<pair<int, int>> occupiedPositionRanges;
        for (auto& o : _Objects)
        {
            _PosY = rd() % 480 + 20;
            while (true)
            {
                bool positionOccupied = false;
                for (const auto& range : occupiedPositionRanges)
                {
                    if (_PosY >= range.first && _PosY <= range.second)
                    {
                        positionOccupied = true;
                        break;
                    }
                }
                if (!positionOccupied)
                {
                    break;
                }
                _PosY = rd() % 480 + 20;
            }
            o._Direction = (Direction)(rd() % 2);
            if (o._Direction == DIR_RIGHT)
            {
                _PosX = 0;
            }
            else
            {
                _PosX = 770;
            }
            o.setPosition(_PosX, _PosY);
            occupiedPositionRanges.push_back({ _PosY - 35.f, _PosY + 35.f });
        }
    }

    void intersection(Gun& gun)
    {
        for (auto it = _Objects.begin(); it != _Objects.end();)
        {
            gun._LaserPosEndX = gun._Laser.getPosition().x + 800.f * cos((gun._Angle + 90) * 3.14159265 / 180);
            gun._LaserPosEndY = gun._Laser.getPosition().y + 800.f * sin((gun._Angle + 90) * 3.14159265 / 180);

            gun._A = gun._LaserPosEndY - gun._Laser.getPosition().y;
            gun._B = gun._Laser.getPosition().x - gun._LaserPosEndX;
            gun._C = gun._LaserPosEndX * gun._Laser.getPosition().y - gun._Laser.getPosition().x * gun._LaserPosEndY;
            if (it->_TypeObj == 1)
            {
                float distance = abs(gun._A * getCenterCircle(it).x + gun._B * getCenterCircle(it).y + gun._C) / sqrt(gun._A * gun._A + gun._B * gun._B);
                if (distance <= circleRadius)
                {
                    Gun::_Intersec = true;
                    _Count++;
                }
                else
                {
                    Gun::_Intersec = false;
                }
                if (Gun::_Intersec)
                {
                    it = _Objects.erase(it);
                }
                else
                {
                    it++;
                }
            }
            else
            {
                if ((gun._A * it->getPosition().x + gun._B * it->getPosition().y + gun._C) * (gun._A * (it->getPosition().x + squareWidth) + gun._B * it->getPosition().y + gun._C) <= 0 ||
                    (gun._A * (it->getPosition().x + squareWidth) + gun._B * it->getPosition().y + gun._C) * (gun._A * (it->getPosition().x + squareWidth) + gun._B * (it->getPosition().y + squareHeight) + gun._C) <= 0 ||
                    (gun._A * (it->getPosition().x + squareWidth) + gun._B * (it->getPosition().y + squareHeight) + gun._C) * (gun._A * it->getPosition().x + gun._B * (it->getPosition().y + squareHeight) + gun._C) <= 0 ||
                    (gun._A * it->getPosition().x + gun._B * (it->getPosition().y + squareHeight) + gun._C) * (gun._A * it->getPosition().x + gun._B * it->getPosition().y + gun._C) <= 0)
                {
                    Gun::_Intersec = true;
                    _Count++;
                }
                else
                {
                    Gun::_Intersec = false;
                }
                if (Gun::_Intersec)
                {
                    it = _Objects.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }

    void moveObjects()
    {
        for (auto it = _Objects.begin(); it != _Objects.end();)
        {
            if (it->getPosition().x < 0 || it->getPosition().x > 770)
            {
                it = _Objects.erase(it);
            }
            else
            {
                if (it->_Direction == DIR_RIGHT)
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
        if (_Objects.empty())
            return true;
    }

    void drawObjects(RenderWindow& window)
    {
        for (auto& o : _Objects)
        {
            if (o._TypeObj == 0)
            {
                window.draw(o._Square);
            }
            else if (o._TypeObj == 1)
            {
                window.draw(o._Circle);
            }
        }
    }

private:
    list<Object> _Objects;
};

int Object::_Count = 0;
Font font;

class Score
{
public:

    Score()
    {
        string FileName = "D:\\изучение c++\\StrikeGame\\x64\\Debug\\font\\ofont.ru_Europe.ttf";
        if (!font.loadFromFile(FileName))
        {
            cout << "error" << endl;
        }
        _ScoreText.setFont(font);
        _ScoreText.setString(L"Score: 0");
        _ScoreText.setCharacterSize(18);
        _ScoreText.setFillColor(Color::Green);
        _ScoreText.setPosition(600.f - _ScoreText.getGlobalBounds().width, 5.f);

        openRecord();
        _Record.setFont(font);
        _Record.setString(L"Record Score: " + to_string(_RecordNum));
        _Record.setCharacterSize(18);
        _Record.setPosition(200.f, 5.f);

    }

    void scoreChage()
    {
        if (Object::_Count > 0)
        {
            _Score += Object::_Count;
            _ScoreText.setString(L"Score: " + to_string(_Score));
            _ScoreText.setFillColor(Color::Green);
            Object::_Count = 0;
        }
        else
        {
            _Score -= 3;
            if (_Score < 0)
                _Score = 0;
            _ScoreText.setString(L"Score: " + to_string(_Score));
            _ScoreText.setFillColor(Color::Red);
        }
    }

    void updateColor(int diff)
    {
        if (Object::_Count == 0)
        {
            _Timer -= diff;
            if (_Timer < 0)
            {
                _ScoreText.setFillColor(Color::Green);
                _Timer = 1500;
            }
        }
    }

    void saveRecord()
    {
        ofstream file;
        file.open("record.txt");
        if (_RecordNum < _Score)
            _RecordNum = _Score;
        file << _RecordNum;
        file.close();
    }

    void openRecord()
    {
        ifstream file("record.txt");
        if (!file.is_open())
        {
            _RecordNum = 0;
        }
        file >> _RecordNum;
        file.close();
    }

    void drawScore(RenderWindow& window)
    {
        window.draw(_ScoreText);
        window.draw(_Record);
    }

private:

    int _Score = 0;
    Text _ScoreText;
    int _Timer = 1500;
    Text _Record;
    string _ScoreRecord;
    int _RecordNum = 0;
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
                _Gun.createLaser();
                _Gun.setIsActiveLaser(true);
                _Gun.duration();
                _List.intersection(_Gun);
                _Score.scoreChage();
            }
        }
        Time time2 = clock.getElapsedTime();
        int diff = time2.asMilliseconds() - time.asMilliseconds();
        time = time2;

        _Gun.updateLaser(diff);
        _Score.updateColor(diff);

        if (_List.isListEmpty())
        {
            _List.createObjects();
            _List.spawnObject();
        }
        _List.moveObjects();

        window.clear();
        _Score.drawScore(window);
        _GunStand.draw(window);
        _Gun.draw(window);
        _List.drawObjects(window);
        window.display();

    }
    _Score.saveRecord();
    return 0;
}


