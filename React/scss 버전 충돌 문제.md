

## error
```text
Failed to compile.

./src/assets/scss/Index.scss (./node_modules/css-loader/dist/cjs.js??ref--6-oneOf-5-1!./node_modules/postcss-loader/src??postcss!./node_modules/resolve-url-loader??ref--6-oneOf-5-3!./node_modules/sass-loader/dist/cjs.js??ref--6-oneOf-5-4!./src/assets/scss/Index.scss)
Error: Missing binding E:\project\covengers\hungry-chat-react\node_modules\node-sass\vendor\win32-x64-57\binding.node
Node Sass could not find a binding for your current environment: Windows 64-bit with Node.js 8.x   

Found bindings for the following environments:
  - Windows 64-bit with Node.js 14.x
  ```
 
 npm install을 하고 모듈 설치를 한 후 npm start를 했을 때 이러한 오류가 뜨며 리액트가 실행되지 않았다.
 
## 해결

scss 문제는 대개 버전 관련 문제라고 한다. 오래 전 업데이트를 한 후 이후로 업데이트가 없어서 최신 버전의 Java 나 Node를 사용할 경우 해당 오류가 발생하게 된다.

- Java version 8~11
- Node version 14
    - Node 16 이나 8 이면 Node 제거하고 재설치

