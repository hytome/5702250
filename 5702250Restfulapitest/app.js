//---------------------------------------------
// app.js
// 간단한 로컬서버 RESTful API 예제
// ---------------------------------------------

const express = require('express');
const app = express();

// (A) Express에 내장된 미들웨어로,
//     HTTP 요청 바디를 JSON 형식으로 파싱
app.use(express.json());

// (B) 자원(데이터)을 임시로 메모리에 저장할 배열
//     --> 실제 REST 서비스에서는 DB를 쓰지만,
//         여기선 예시로 dataList가 '자원' 역할
let dataList = [];

// (1) GET /5702250/wellCome
//     - RESTful에서 GET 메서드는 "자원 조회"에 사용
//     - '/5702250/welCome'은 'welcome' 자원(혹은 메시지 자원)을 명사형으로 표현
app.get('/5702250/welCome', (req, res) => {
  // JSON 형태로 응답 (Representation)
  // RESTful에서 주로 사용되는 형식입니다.
  res.json({ message: '5702250 허현 방문자님 환영합니다.' });
});

// (2) POST /5702250/data
//     - RESTful에서 POST 메서드는 "자원 생성/추가"에 사용합니다. 
//     - '/5702250/data'라는 URI로, 클라이언트가 JSON 형식의 데이터를 전송합니다.
app.post('/5702250/data', (req, res) => {
  // req.body: Express가 JSON을 파싱해 준 결과
  const clientData = req.body;

  // 서버에 임시로 dataList라는 배열을 두어
  // 새 데이터를 추가 (create)합니다.
  dataList.push(clientData);

  // 응답: 새로 받은 데이터 + 메시지
  // -> JSON으로 반환하여 RESTful 형식 유지 (Representation 일관성)
  res.json({
    receivedData: clientData,
    message: 'POST 요청이 성공적으로 받아졌습니다.',
  });
});

// (3) GET /5702250/data
//     - RESTful에서 GET 메서드는 자원을 "읽기(조회)"할 때 사용합니다.
//     - 지금까지 서버에 저장된 dataList 전체를 클라이언트에게 반환 합니다.
//     - 상태 코드는 기본적으로 200(OK)이 자동 전송
app.get('/5702250/data', (req, res) => {
  res.json({
    receivedData: dataList,
    message: 'GET 요청이 성공적으로 받아졌습니다. 데이터 목록을 반환합니다.',
  });
});

// (4) 무상태성(Stateless)
//     - 여기서는 세션이나 쿠키를 별도로 관리하지 않습니다.
//     - 서버가 클라이언트의 "로그인 상태" 등을 보관하지 않으므로,
//       각 요청은 독립적으로 처리 (REST의 핵심 원칙 중 하나)
// 나중에 mysql등 db를 공부하면서 좀더 보완해야할 점입니다.

// (5) 서버를 3000번 포트에서 실행
//     - 브라우저나 Postman에서 http://localhost:3000/ 으로 접근 가능
app.listen(3000, () => {
  console.log('RESTful API server is running on http://localhost:3000');
});
