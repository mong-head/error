### 상황
* Chatting app 개발 (socket.io,redis 이용 구현)
* 개발 환경
  * backend : node
  * frontend : React

* 문제 상황
  * server(node)쪽에서 client(React)쪽으로 메세지를 보내줄 때마다 메세지를 보낼 때마다 메세지 받고 출력하는 이벤트가 급수적으로 추가적으로 불러져서 동일한 메세지가 여러개 생성되었습니다.

### 문제
React에서 아무 장소에서나 socket 이벤트 호출(```socket.on('message',function)```)하는 코드를 작성하니 rendering 될 때마다 socket이 하나씩 추가되어 이벤트도 그에 따라 여러번 호출되는 현상이 발생하였습니다. 

즉, 한 번 rendering될 때마다 socket이 하나씩 추가되고, 하나의 이벤트가 발생할 것이라고 예상한 것이 실제로는 생성된 socket수 만큼 이벤트를 발생하였기에 rendering한  수가 2번이면 socket 수가 2개이고, 이벤트도 2번 호출되었습니다.

### 해결
찾아보니 rendering될 때마다 socket은 계속 생성되는 것이 맞습니다. 다만, 문제는 생성된 모든 socket 객체가 event를 실행하는 데에 있었습니다. 

이 문제는 react component life-cycle과 관련이 있습니다. socket 호출(```socket.on```)부분은 component가 한 번 mount된 후(즉, 처음 socket이 생성되었을 때)만 호출되어야 합니다. component update될 때마다 socket 호출이 있게되면 생성된 소켓 수만큼 호출되게 됩니다. 따라서 한 번 mount된 직후에만 호출될 수 있도록(socket이 처음 생성된 후에만) 만드시면 됩니다.

따라서, **class component**인 경우, 밑처럼 ```componentDidMount```내에서만 ```socket.on```을 하시면 됩니다.
```js
componentDidMount() {
  socket.on("comment", (info) => {
    this.textAreaAdd(info.name, info.room, info.message)
  }) 
}
```

**function component**인 경우, 밑처럼 hook함수인 useEffect를 이용해서 하시면 됩니다.
```js
useEffect(() => {
  socket.on("comment", (info) => {
    this.textAreaAdd(info.name, info.room, info.message)
}, []);
```
