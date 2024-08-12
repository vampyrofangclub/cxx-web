extern "C" int JS(int, void*);
auto js(auto...args){
  auto lambda = [args...](){};
  return JS(sizeof...(args), &lambda);
}

extern void* __heap_base;

extern "C" void* malloc(int size){
  static auto MemPtr = (int)&__heap_base; 
  auto ptr = MemPtr;
  MemPtr += size;
  return (void*)ptr;
}

auto numAddStr(auto num, auto& str){
  char buf[10] = {};
  auto size = 0;
  if(num == 0){
    buf[size++] = '0';
  } else {
    while(num > 0){
      auto temp = num/10;
      auto rem = num - temp * 10;
      buf[size++] = '0' + rem;
      num = temp;
    }
  }
  auto ptr = (char*)malloc(sizeof(str) - 1 + size + 1);
  for(auto i = 0; i < size; i += 1){
    char chr = buf[size - 1 - i];
    ptr[i] = chr;
  }
  for(auto i = 0;i < sizeof(str)-1; i += 1){
    char chr = str[i];
    ptr[size+i] = chr;
  }
  ptr[sizeof(str) - 1 + size] = '\0';
  return (const char*)ptr;
}
auto strAddNum(auto& str, auto num){
  char buf[10] = {};
  auto size = 0;
  if(num == 0){
    buf[size++] = '0';
  } else {
    while(num > 0){
      auto temp = num/10;
      auto rem = num - temp * 10;
      buf[size++] = '0' + rem;
      num = temp;
    }
  }
  auto ptr = (char*)malloc(sizeof(str) - 1 + size + 1);
  ptr[sizeof(str) - 1 + size] = '\0';
  for(auto i = 0; i < sizeof(str)-1; i += 1){
    char chr = str[i];
    ptr[i] = chr;
  }
  for(auto i = 0; i < size; i += 1){
    char chr = buf[size - 1 - i];
    ptr[sizeof(str) - 1 + i] = chr;
  }
  return (const char*)ptr;
}

struct Listener {
  void* lambda;
  void(*fn)(void*);
  Listener(auto listener): lambda(listener), fn(+[](void* lambda){ (*static_cast<decltype(listener)>(lambda))(); }){}
};
extern "C" void OnEvent(void* ptr){
  auto listener = static_cast<Listener*>(ptr);
  listener->fn(listener->lambda);
}

void* operator new(unsigned long count){ 
  auto ptr = malloc(count);
  return ptr;
}

struct $Frame {
  int el;
  $Frame(): el(js("()=>$.set(document.createElement('div'))")){ 
    js(el, "(el)=>$.get(el).style.display = 'flex'");
    js(el, "(el)=>$.get(el).style.flexDirection = 'column'");
    js(el, "(el)=>$.get(el).style.boxSizing = 'border-box'");
  }

  auto& width(auto val){ js(el, val, "(el, val)=>$.get(el).style.width = val + 'px'"); return *this; }
  auto& height(auto val){ js(el, val, "(el, val)=>$.get(el).style.height = val + 'px'"); return *this; }

  auto& marginAuto(){ js(el, "(el)=>$.get(el).style.margin = 'auto'"); return *this; }
  auto& marginAutoLeft(){ js(el, "(el)=>$.get(el).style.marginLeft = 'auto'"); return *this; }
  auto& marginAutoRight(){ js(el, "(el)=>$.get(el).style.marginRight = 'auto'"); return *this; }
  auto& marginAutoTop(){ js(el, "(el)=>$.get(el).style.marginTop = 'auto'"); return *this; }
  auto& marginAutoBottom(){ js(el, "(el)=>$.get(el).style.marginBottom = 'auto'"); return *this; }

  auto& marginLeft(auto val){ js(el, val, "(el, val)=>$.get(el).style.marginLeft = val + 'px'"); return *this; }
  auto& marginRight(auto val){ js(el, val, "(el, val)=>$.get(el).style.marginRight = val + 'px'"); return *this; }
  auto& marginTop(auto val){ js(el, val, "(el, val)=>$.get(el).style.marginTop = val + 'px'"); return *this; }
  auto& marginBottom(auto val){ js(el, val, "(el, val)=>$.get(el).style.marginBottom = val + 'px'"); return *this; }

  auto& padding(auto val){ js(el, val, "(el, val)=>$.get(el).style.padding = val + 'px'"); return *this; }
  auto& paddingLeft(auto val){ js(el, val, "(el, val)=>$.get(el).style.paddingLeft = val + 'px'"); return *this; }
  auto& paddingRight(auto val){ js(el, val, "(el, val)=>$.get(el).style.paddingRight = val + 'px'"); return *this; }
  auto& paddingTop(auto val){ js(el, val, "(el, val)=>$.get(el).style.paddingTop = val + 'px'"); return *this; }
  auto& paddingBottom(auto val){ js(el, val, "(el, val)=>$.get(el).style.paddingBottom = val + 'px'"); return *this; }

  auto& border(auto val){ js(el, val, "(el, val)=>$.get(el).style.border = $.getStr(val)"); return *this; }
  auto& borderRadius(auto val){ js(el, val, "(el, val)=>$.get(el).style.borderRadius = val + 'px'"); return *this; }
  auto& borderTop(auto val){ js(el, val, "(el, val)=>$.get(el).style.borderTop = $.getStr(val)"); return *this; }

  auto& fontSize(auto val){ js(el, val, "(el, val)=>$.get(el).style.fontSize = val + 'px'"); return *this; }
  auto& fontFamily(auto val){ js(el, val, "(el, val)=>$.get(el).style.fontFamily = $.getStr(val)"); return *this; }
  auto& fontWeight(auto val){ js(el, val, "(el, val)=>$.get(el).style.fontWeight = val"); return *this; }
  auto& color(auto val){ js(el, val, "(el, val)=>$.get(el).style.color = $.getStr(val)"); return *this; }
  auto& lineHeight(auto val){ js(el, val, "(el, val)=>$.get(el).style.lineHeight = val + 'px'"); return *this; }


  auto& alignSelf(auto val){ js(el, val, "(el, val)=>$.get(el).style.alignSelf = $.getStr(val)"); return *this; }
  auto& alignItems(auto val){ js(el, val, "(el, val)=>$.get(el).style.alignItems = $.getStr(val)"); return *this; }
  auto& flexDirection(auto val){ js(el, val, "(el, val)=>$.get(el).style.flexDirection = $.getStr(val)"); return *this; }

  auto& backgroundColor(auto val){ js(el, val, "(el, val)=>$.get(el).style.backgroundColor = $.getStr(val)"); return *this; }
  auto& boxShadow(auto val){ js(el, val, "(el, val)=>$.get(el).style.boxShadow = $.getStr(val)"); return *this; }

  auto& textContent(auto val){ js(el, val, "(el, val)=>$.get(el).textContent = $.getStr(val)"); return *this; }
  auto& addChild(auto&& child){ js(el, child.el, "(el, childEl)=>$.get(el).appendChild($.get(childEl))"); return *this; }
  auto& children(auto count, auto&& fn){ for(auto i = 0; i < count; i += 1) addChild(fn()); return *this; }
  auto& onClick(auto fn){ 
    js(el, new Listener(fn), "(el, fn)=>$.get(el).onclick = ()=>$.instance.exports.OnEvent(fn)"); 
    js(el, "(el)=>$.get(el).style.cursor = 'pointer'");
    return *this; 
  }
};
auto& Frame(){ return *new $Frame(); }

struct $Input {
  int el;
  $Input(): el(js("()=>$.set(document.createElement('input'))")){
    js(el, "(el)=>$.get(el).style.outline = 'none'");
    js(el, "(el)=>$.get(el).style.border = 'none'");
    js(el, "(el)=>$.get(el).style.width = '100%'");
    js(el, "(el)=>$.get(el).style.height = '100%'");
    js(el, "(el)=>$.get(el).style.font = 'inherit'");
    js(el, "(el)=>$.get(el).style.padding = '0px'");
  }
  auto& value(auto val){ js(el, val, "(el, val)=>$.get(el).value = $.getStr(val)"); return *this; }
  auto& placeholder(auto val){ js(el, val, "(el, val)=>$.get(el).placeholder = $.getStr(val)"); return *this; }
  auto& onInput(auto fn){ js(el, new Listener(fn), "(el, fn)=>$.get(el).oninput = ()=>$.instance.exports.OnEvent(fn)");  return *this; }
  auto& onKeyDown(auto fn){ js(el, new Listener(fn), "(el, fn)=>$.get(el).onkeydown = ()=>$.instance.exports.OnEvent(fn)");  return *this; }
  auto& focus(auto doFocus = true){ if(doFocus) js(el, "(el)=>setTimeout(()=>$.get(el).focus())"); return *this; }
  auto& onFocus(auto fn){ js(el, new Listener(fn), "(el, fn)=>$.get(el).onfocus = ()=>$.instance.exports.OnEvent(fn)");  return *this; }
  auto& onBlur(auto fn){ js(el, new Listener(fn), "(el, fn)=>$.get(el).onblur = ()=>setTimeout(()=>$.instance.exports.OnEvent(fn))");  return *this; }
};
auto& Input(){
  return *new $Input();
}

struct $Vector {
  int el;
  int pathEl;
  $Vector(){
    el = js("()=>$.set(document.createElementNS('http://www.w3.org/2000/svg', 'svg'))");
    js(el, "(el)=>$.get(el).style.outline = 'none'");
    pathEl = js("()=>$.set(document.createElementNS('http://www.w3.org/2000/svg', 'path'))");
    js(el, pathEl, "(el, pathEl)=>$.get(el).appendChild($.get(pathEl))");
  }
  auto& fill(auto val){ js(pathEl, val, "(el, val)=>$.get(el).setAttribute('fill', $.getStr(val))"); return *this; }
  auto& d(auto val){ js(pathEl, val, "(el, val)=>$.get(el).setAttribute('d', $.getStr(val))"); return *this; }
};
auto& Vector(){
  return *new $Vector();
}



$Frame& App();

auto rerender(){
  auto& frame = App();
  js("()=>document.body.firstElementChild.textContent = ''");
  js(frame.el, "(el)=>document.body.firstElementChild.appendChild($.get(el))");
}

struct TodoModel {
  TodoModel* next;
  TodoModel* prev;
  const char* name = "";
  bool completed = false;
};
struct AppModel {
  int windowWidth = js("()=>window.innerWidth");
  int windowHeight = js("()=>window.innerHeight");
  const char* NewTodoText = "";
  bool NewTodoTextFocused = false;
  const char* FilterTodosName = "All";
  TodoModel* firstTodo = nullptr;
  TodoModel* lastTodo = nullptr;
  int todoCount = 0;
};
auto AppState = new AppModel();

auto& Todo(auto todo){
  return Frame()
    .borderTop("1px solid #EDEDED")
    .paddingTop(14)
    .paddingBottom(16)
    .flexDirection("row")
    .addChild(Frame()
      .width(30)
      .height(30)
      .marginLeft(19)
      .border(todo->completed ? "0.888889px solid #5DC2AF" : "0.888889px solid #D5D4D4")
      .onClick(new auto([=](){
          todo->completed = !todo->completed;
          rerender();
      }))
      .addChild(todo->completed ? Frame()
              .marginAuto()
              .width(16)
              .height(16)
              .addChild(Vector().fill("#5DC2AF").d("M 14.518518518518517 0 L 5.62962962962963 13.629630279541017 L 1.1851851851851851 9.185185623168946 L 0 10.370370864868164 L 5.925925925925926 16.296297073364258 L 16 0.8888889312744142 L 14.518518518518517 0 Z"))
          : Frame())
    )
    .addChild(Frame()
        .marginLeft(29)
        .fontFamily("sans-serif")
        .fontSize(24)
        .fontWeight(100)
        .lineHeight(29)
        .color("#737373")
        .textContent(todo->name)
      )
    .addChild(Frame()
        .alignSelf("center")
        .width(17)
        .height(17)
        .marginAutoLeft()
        .marginRight(17)
        .onClick(new auto([=](){
          if (todo->prev){
            todo->prev->next = todo->next;
          } else {
            AppState->firstTodo = todo->next;
          }
          AppState->todoCount -= 1;
          rerender();
        }))
        .addChild(Vector().fill("#B68B8B").d("M 14.936514401380126 16.4725399017334 L 0 1.5360246472657362 L 1.5492663519509156 0 L 16.48577880859375 14.936514513615355 L 14.936514401380126 16.4725399017334 Z M 1.5492663519509156 16.4725399017334 L 0 14.936514513615355 L 14.936514401380126 0 L 16.48577880859375 1.5360246472657362 L 1.5492663519509156 16.4725399017334 Z"))
    );
}

auto& NewTodo(){
  return Frame()
    .paddingTop(21)
    .paddingBottom(16)
    .alignItems("center")
    .flexDirection("row")
    .addChild(Frame()
        .width(21)
        .height(11)
        .marginLeft(25)
        .addChild(Vector().fill("rgba(115, 115, 115, 1)").d("M 0 0 L 0 4.829267918248088 L 10.5 11 L 21 4.853657786684188 L 21 4.332577070733386e-15 L 10.5 6.31707222278235 L 0 0 Z")))
    .addChild(Frame()
        .marginLeft(20)
        .width(400)
        .height(29)
        .fontFamily("sans-serif")
        .fontSize(24)
        .fontWeight(100)
        .lineHeight(29)
        .color("#737373")
        .addChild(Input()
            .value(AppState->NewTodoText)
            .placeholder("What needs to be done?")
            .onInput(new auto([](){
              AppState->NewTodoText = (const char*)js("()=>$.setStr(window.event.target.value)");
              //rerender();
            }))
            .focus(AppState->NewTodoTextFocused)
            .onFocus(new auto([](){ AppState->NewTodoTextFocused = true; }))
            .onBlur(new auto([](){ AppState->NewTodoTextFocused = false; }))
            .onKeyDown(new auto([](){
              if(js("()=>window.event.code === 'Enter'")){
                AppState->lastTodo = AppState->lastTodo->next = new TodoModel{.name = AppState->NewTodoText};
                if(AppState->todoCount == 0) AppState->firstTodo = AppState->lastTodo;
                AppState->todoCount += 1;
                AppState->NewTodoText = "";
                rerender();
              }
            }))
    ));
}

auto& Footer(){
  return Frame()
    .borderTop("1px solid #EDEDED")
    .paddingLeft(23)
    .paddingRight(10)
    .paddingTop(12)
    .paddingBottom(12)
    .alignItems("center")
    .flexDirection("row")
    .addChild(Frame()
        .fontFamily("sans-serif")
        .fontSize(14)
        .lineHeight(17)
        .fontWeight(100)
        .textContent(numAddStr([](){
          auto num = 0;
          for(auto node = AppState->firstTodo; node != nullptr; node = node->next){
            if(!node->completed) num += 1;
          }
          return num;
        }(), " items left"))
    )
    .addChild(Frame()
        .marginAutoLeft()
        .marginAutoRight()
        .flexDirection("row")
        .addChild(Frame()
            .padding(4)
            .fontFamily("sans-serif")
            .fontSize(14)
            .lineHeight(17)
            .fontWeight(100)
            .border(AppState->FilterTodosName == "All" ? "1px solid #F2CCD2" : "none")
            .borderRadius(3)
            .onClick(new auto([](){
              AppState->FilterTodosName = "All";
              rerender();
            }))
            .textContent("All")
        )
        .addChild(Frame()
            .padding(4)
            .fontFamily("sans-serif")
            .fontSize(14)
            .lineHeight(17)
            .fontWeight(100)
            .border(AppState->FilterTodosName == "Active" ? "1px solid #F2CCD2" : "none")
            .borderRadius(3)
            .onClick(new auto([](){
              AppState->FilterTodosName = "Active";
              rerender();
            }))
            .textContent("Active")
        )
        .addChild(Frame()
            .padding(4)
            .fontFamily("sans-serif")
            .fontSize(14)
            .lineHeight(17)
            .fontWeight(100)
            .border(AppState->FilterTodosName == "Completed" ? "1px solid #F2CCD2" : "none")
            .borderRadius(3)
            .onClick(new auto([](){
              AppState->FilterTodosName = "Completed";
              rerender();
            }))
            .textContent("Completed")
        )
    )
    .addChild(Frame()
        .padding(4)
        .fontFamily("sans-serif")
        .fontSize(14)
        .lineHeight(17)
        .fontWeight(100)
        .onClick(new auto([](){
          //todo
        }))
        .textContent("Clear completed")
      )
  
;};

$Frame& App(){
  return Frame()
    .backgroundColor("#F5F5F5")
    .alignItems("center")
    .width(AppState->windowWidth)
    .height(AppState->windowHeight)
    .addChild(Frame()
        .marginTop(106)
        .fontSize(100)
        .fontFamily("sans-serif")
        .fontWeight(200)
        .color("rgba(175, 47, 47, 0.15)")
        .lineHeight(121)
        .textContent("todos"))
    .addChild(Frame()
        .marginTop(31)
        .backgroundColor("white")
        .width(450)
        .boxShadow("0px 0px 4px rgba(0, 0, 0, 0.25), 0px 25px 50px rgba(0, 0, 0, 0.25)")
        .addChild(NewTodo())
        .addChild(Frame()
          .children(AppState->todoCount, [node = AppState->firstTodo]() mutable -> auto& {
            auto todo = node;
            node = node->next;
            return Todo(todo);
          }))
        .addChild(Footer())
    );
}

int main() {
  js(new Listener(new auto([](){
    AppState->windowWidth = js("()=>window.innerWidth");
    AppState->windowHeight = js("()=>window.innerHeight");
    rerender();
  })), "(fn)=>window.onresize = ()=>$.instance.exports.OnEvent(fn)");
  for(auto i = 0; i < 5; i += 1){
    AppState->lastTodo = AppState->lastTodo->next = new TodoModel{.prev = AppState->lastTodo, .name = strAddNum("todo", AppState->todoCount)};
    if(AppState->todoCount == 0) AppState->firstTodo = AppState->lastTodo;
    AppState->todoCount += 1;
  }
  rerender();
  return 123;
}