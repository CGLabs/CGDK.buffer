## CGDK::buffer 설정하기.
특별한 설정은 없습니다만
- C++17이상의 버전 설정<br>
- ``CGDK.buffer/C++/include``를 ``include`` 디렉토리에 포함시켜 주십시요.<br>
- 소스 파일에 ``#include "cgdk/shared_buffer"``를 추가해 사용하시면 됩니다.<br>
visual studio, linux, unreal 3D 모두 설정이 동일합니다.<br>
자세한 설정 방법은 [설명 문서](https://github.com/CGLabs/CGDK.buffer/blob/master/C%2B%2B/document/Getting_start_CGDK.buffer.pptx)를 참조해 주십시요.<br>
<br>

### '/project'
- 그냥 ``CGDK::buffer``를 ``visual studio``에서 볼 수 있도록 project를 만들어 놓은 것일 뿐 header 파일로만 되어 있어 컴파일을 하실 필요 없고 할 수도 없습니다.<br>
<br>

### '/tutorials'
#### comment
   - 5개의 튜터리얼로 구성되어 있습니다.<br>
      [tutorial 1] 기본 사용법: 다양한 자료형 직렬화/역직렬화를 위한 ``append``/``extract``/``front`` 함수 등의 사용법을  설명합니다.<br>
      [tutorial 2] 버퍼 조작: 버퍼 자체를 조작하는 방법들을 설명합니다. (버퍼 깊은 복사, ``CGDK::buffer_view``와 ``CGDK::buffer`` 용도, 버퍼 연사자 등...)<br>
      [tutorial 3] 구조체 직렬화: idl을 대신한 구조체 직렬화의 사용법과 예제를 보여줍니다.<br>
      [tutorial 4] ``Ibuffer_serialzation``: 사용자 정의 schemaless 직렬화를 설정합니다. 구조체 직렬화를 사용하기 힘들거나 직접 직렬화/역직렬화를 정의할 필요가 있은 때 사용합니다.<br>
      [tutorial 5] unreal 3D 예제: (필요 이상으로 커서 포함하시지 않았습니다.)<br>
      [tutorial 6] 정적 버퍼: ``CGDK::buffer``를 사용해 배열이나 ``std::array``와 같은 정적 변수를 버퍼로 사용하는 벙법을 설명합니다.<br>
#### compile
   - Visual studio는 프로젝트 파일(``CGDK.buffer.github/C++/tutorial/CGDK.buffer.tutorial.vs17.sln``)을 열어서 컴파일 하시면 됩니다.<br>
   - Linux는 ``CMake``를 사용해서 컴파일 하시면 됩니다.<br>
   ``CGDK.buffer.github/C++/tutorial`` 디렉토리에서<br>
``` bash
      > CMake . -DCMAKE_BUILD_TYPE=Debug 
      > make
```
   를 실행하시면 됩니다. ``Release``로 컴파일을 원하실 경우 ``-DCMAKE_BUILD_TYPE``옵션을 Release로만 바꾸어 주시면 됩니다.<br>
<br>

### '/uint_test'
#### comment
   - unit test는 ``google test``를 사용하여 작성되었습니다.<br>
   - 2가지의 unit test가 있습니다.<br>
   ``unit_test.benchmark.basic`` : ``protobuf``,``flatbuffers``와의 성능 비교를 위한 unit test입니다.<br>
   ``unit_test.function`` : ``CGDK::buffer``의 오류가 없는지를 검사하는 unit test입니다.<br>
#### compile
   - Visual studio는 프로젝트 파일('CGDK.buffer.github/C++/unit_test/CGDK.buffer.unit_test.vs17.sln')을 열어서 컴파일 하시면 됩니다.<br>
   - ``vcpkg``를 사용하므로 필요한 모듈(``gtest``,``protobuf``,``flatbuffers``)는 ``CGDK.buffer/C++/unit_test/vcpkg_installed``에 자동으로 설치됩니다.<br>
   - Linux를 사용하실 경우 ``CMake``를 사용해서 컴파일 하시면 됩니다.<br>
   - 하지만 사전에 ``gtest``,``protobuf``,``flatbuffers``를 설치하시길 바랍니다.<br>
   [ubuntu 기준]<br>
   ``` bash
      > sudo apt install libgtest-dev
      > sudo apt install protobuf-compile
      > snap install flatbuffers
   ```
   로 설치하시면 됩니다.<br>
   그 이후에 ``CGDK.buffer.github/C++/unit_test`` 디렉토리에서<br>
   ``` bash
      > CMake . -DCMAKE_BUILD_TYPE=Debug 
      > make
   ```
   를 실행하시면 됩니다. Release로 컴파일을 원하실 경우 ``-DCMAKE_BUILD_TYPE``옵션을 Release로만 바꾸어 주시면 됩니다.<br>

