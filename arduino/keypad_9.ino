// Minimal class to replace std::vector
template<typename Data>
class Vector {
  size_t d_size; // Stores no. of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  public:
    Vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor
    Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); }; // Copy constuctor
    ~Vector() { free(d_data); }; // Destructor
    Vector &operator=(Vector const &other) { free(d_data); d_size = other.d_size; d_capacity = other.d_capacity; d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); return *this; }; // Needed for memory management
    void push_back(Data const &x) { if (d_capacity == d_size) resize(); d_data[d_size++] = x; }; // Adds new value. If needed, allocates more space
    size_t size() const { return d_size; }; // Size getter
    Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter
    Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter
  private:
    void resize() { d_capacity = d_capacity ? d_capacity*2 : 1; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space
};

//////////////////////////////////////////////////////////

enum ButtonState { btNone, btPress, btRelease };
enum ActionType  { atOnce, atKeep, atFunc };

typedef  struct {
  int pin;
  ButtonState state;
} ButtonInfo;

const static int buttonCount = 9;

/*
 * kekpad
 * 6 7 8 
 * 3 4 5
 * 0 1 2
 * Number 8 : It changes the keypad page.
 */

ButtonInfo buttonList[buttonCount] = {
  {16, btRelease},
  {18, btRelease},
  {21, btRelease},
  {10, btRelease},
  {15, btRelease},
  {20, btRelease},
  {9, btRelease},
  {14, btRelease},
  {19, btRelease}
};

typedef  struct {
  ActionType actionType;
  Vector<int> msg;
} MsgInfo;

// [currPage][Button]
MsgInfo keyMsg[3][buttonCount];

int currPage = 2;

//////////////////////////////////////////////////////////

void setup() {
  
  // LED Pin
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  // KeyPad Pin
  for( int i = 0; buttonCount > i ; i++  )
  {
    pinMode(buttonList[i].pin, INPUT_PULLUP);
  }
  
///////////////////////////////////////////////////////
// 0 page
  keyMsg[0][0].actionType = atOnce;
  keyMsg[0][0].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[0][0].msg.push_back('c');

  keyMsg[0][1].actionType = atOnce;
  keyMsg[0][1].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[0][1].msg.push_back('v');

  keyMsg[0][2].actionType = atOnce;
  keyMsg[0][2].msg.push_back(KEY_RETURN);

  keyMsg[0][3].actionType = atKeep;
  keyMsg[0][3].msg.push_back(KEY_LEFT_SHIFT);

  keyMsg[0][4].actionType = atKeep;
  keyMsg[0][4].msg.push_back(KEY_LEFT_CTRL);

  keyMsg[0][5].actionType = atKeep;
  keyMsg[0][5].msg.push_back(KEY_BACKSPACE);

  keyMsg[0][6].actionType = atOnce;
  keyMsg[0][6].msg.push_back(KEY_ESC);

  keyMsg[0][7].actionType = atOnce;
  keyMsg[0][7].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[0][7].msg.push_back(KEY_F4);

  keyMsg[0][8].actionType = atFunc;

///////////////////////////////////////////////////////
// 1 page
  keyMsg[1][0].actionType = atOnce;
  keyMsg[1][0].msg.push_back(91);
  keyMsg[1][0].msg.push_back('c');

  keyMsg[1][1].actionType = atOnce;
  keyMsg[1][1].msg.push_back(91);
  keyMsg[1][1].msg.push_back('v');

  keyMsg[1][2].actionType = atOnce;
  keyMsg[1][2].msg.push_back(91);
  keyMsg[1][2].msg.push_back(32);

  keyMsg[1][3].actionType = atKeep;
  keyMsg[1][3].msg.push_back(KEY_LEFT_SHIFT);

  keyMsg[1][4].actionType = atOnce;
  keyMsg[1][4].msg.push_back(KEY_HOME);

  keyMsg[1][5].actionType = atOnce;
  keyMsg[1][5].msg.push_back(KEY_END);

  keyMsg[1][6].actionType = atOnce;
  keyMsg[1][6].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[1][6].msg.push_back(KEY_F4);

  keyMsg[1][7].actionType = atOnce;
  keyMsg[1][7].msg.push_back(KEY_LEFT_ALT);
  keyMsg[1][7].msg.push_back(KEY_F4);

  keyMsg[1][8].actionType = atFunc;

///////////////////////////////////////////////////////
// 2 page
  keyMsg[2][0].actionType = atOnce;
  keyMsg[2][0].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[2][0].msg.push_back('c');

  keyMsg[2][1].actionType = atOnce;
  keyMsg[2][1].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[2][1].msg.push_back('v');

  keyMsg[2][2].actionType = atOnce;
  keyMsg[2][2].msg.push_back(KEY_RETURN);

  keyMsg[2][3].actionType = atKeep;
  keyMsg[2][3].msg.push_back(KEY_LEFT_SHIFT);

  keyMsg[2][4].actionType = atOnce;
  keyMsg[2][4].msg.push_back(KEY_HOME);

  keyMsg[2][5].actionType = atOnce;
  keyMsg[2][5].msg.push_back(KEY_END);

  keyMsg[2][6].actionType = atOnce;
  keyMsg[2][6].msg.push_back(KEY_LEFT_CTRL);
  keyMsg[2][6].msg.push_back(KEY_F4);

  keyMsg[2][7].actionType = atOnce;
  keyMsg[2][7].msg.push_back(KEY_LEFT_ALT);
  keyMsg[2][7].msg.push_back(KEY_F4);

  keyMsg[2][8].actionType = atFunc;
///////////////////////////////////////////////////////  

  setPage();
}

void loop() {
  // put your main code here, to run repeatedly:
  for( int i = 0; buttonCount > i ; i++  )
  {
    if (digitalRead(buttonList[i].pin) == LOW)
    {
      if(buttonList[i].state == btRelease)
      {
        buttonList[i].state = btPress;
        PressMsg(i);
      }
    }
    else
    {
      if(buttonList[i].state == btPress)
      {
        buttonList[i].state = btRelease;
        ReleaseMsg(i);
      }
    }
  }

  delay(10);
}

void setPage()
{
  currPage++;
  if(2 < currPage) 
  {
    currPage = 0;
    Keyboard.begin();
  }

  int counter = 0;
  digitalWrite(4, counter == currPage ? HIGH : LOW);
  counter++;
  digitalWrite(3, counter == currPage ? HIGH : LOW);
  counter++;
  digitalWrite(2, counter == currPage ? HIGH : LOW);

  for( int i = 0; buttonCount-1 > i ; i++ )
  {
    buttonList[i].state = btRelease;
  }

  Keyboard.releaseAll();
}

void PressMsg(int btIdx)
{
	if (atFunc == keyMsg[currPage][btIdx].actionType)
	{
		setPage();
		return;
	}

  for( int i = 0; keyMsg[currPage][btIdx].msg.size() > i ; i++ )
  {
    Keyboard.press(keyMsg[currPage][btIdx].msg[i]);
  }
    
  if( atOnce == keyMsg[currPage][btIdx].actionType )
  {
    delay(100);

    for( int i = 0; keyMsg[currPage][btIdx].msg.size() > i ; i++ )
    {
      Keyboard.release(keyMsg[currPage][btIdx].msg[i]);
    }
  }
}

void ReleaseMsg(int btIdx)
{
  if( atKeep != keyMsg[currPage][btIdx].actionType )
  {
    return;
  }

  for( int i = 0; keyMsg[currPage][btIdx].msg.size() > i ; i++ )
  {
    Keyboard.release(keyMsg[currPage][btIdx].msg[i]);
  }
}

