cmake_minimum_required(VERSION 3.20)
project(MyCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BIN ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${BIN})
set(LIBRARY_OUTPUT_PATH ${BIN})

#PROJECT FILES
set(WINDOW_DIRECTORY ${CMAKE_SOURCE_DIR}/include/Window)
set(PROJECT_SOURCE_FILES
	main.cpp
	${WINDOW_DIRECTORY}/source/Window.cpp
	${WINDOW_DIRECTORY}/source/Window.ui
)
set(PROJECT_HEADER_FILES
	${WINDOW_DIRECTORY}/include/Window.hpp
)

# SET PATH FOR MY WINDOWS // PLS COMMENT THIS IF U HAVE SYSTEM PATH
if(WIN32)
	message(STATUS "Setting path for windows")
	set(qt_root_folder "C:/Qt/6.5.2/msvc2019_64")
	set(Qt${QT_VERSION_MAJOR}_ROOT ${qt_root_folder})
endif()

# FIND QT FRAMEWORK
message(STATUS "Find QT Framework..")
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

if(Qt6_FOUND)
	message(STATUS "QT FOUND!")
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTORCC ON)


	# MACOS BUNDLE PACKAGE
	if(APPLE)
		set(MACOSX_BUNDLE_ICON_FILE icon.png)
		set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
		set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/bin/resources/icons/icon.png")
		set(STYLE_APP "${CMAKE_CURRENT_SOURCE_DIR}/bin/resources/window.qss")
		set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
		set_source_files_properties(${STYLE_APP} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

		qt_add_executable(${PROJECT_NAME} MACOSX_BUNDLE MANUAL_FINALIZATION ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES} ${APP_ICON} ${STYLE_APP})
	endif()

	if(WIN32)
		#MAKE DIR AND COPY RESOURCE FILES FOR EXE FILE
		message(STATUS "Make resources dir")
		file(MAKE_DIRECTORY ${BIN}/Debug/Resources)
		file(MAKE_DIRECTORY ${BIN}/Debug/platforms)
		message(STATUS "Copy file in resources dir")
		file(COPY ${CMAKE_SOURCE_DIR}/res/window.qss DESTINATION ${BIN}/Debug/Resources)
		file(COPY ${CMAKE_SOURCE_DIR}/res/icons/icon.png DESTINATION ${BIN}/Debug/Resources)
		file(COPY ${CMAKE_SOURCE_DIR}/res/icons/icon.ico DESTINATION ${BIN}/Debug/Resources)
		#Qt6 DLL's
		file(COPY ${qt_root_folder}/plugins/platforms/qwindowsd.dll DESTINATION ${BIN}/Debug/platforms)
		file(COPY ${qt_root_folder}/bin/Qt6Cored.dll DESTINATION ${BIN}/Debug)
		file(COPY ${qt_root_folder}/bin/Qt6Guid.dll DESTINATION ${BIN}/Debug)
		file(COPY ${qt_root_folder}/bin/Qt6Widgetsd.dll DESTINATION ${BIN}/Debug)

	   set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug/Resources/icon.ico")
	   qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES} ${APP_ICON})
	endif()

	target_include_directories(${PROJECT_NAME}
		PUBLIC
			$<INSTALL_INTERFACE:include>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			Qt${QT_VERSION_MAJOR}::Widgets
			Qt${QT_VERSION_MAJOR}::Core
	)

	target_link_libraries(${PROJECT_NAME}
		PRIVATE
			Qt${QT_VERSION_MAJOR}::Widgets
			Qt${QT_VERSION_MAJOR}::Core
	)
else()
	message(FATAL_ERROR "QT NOT FOUND!")
endif()
