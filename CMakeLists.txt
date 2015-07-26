cmake_minimum_required(VERSION 3.2)
project(BarbarianQuestII)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
set(CMAKE_BUILD_TYPE Release)

include_directories(include)
include_directories(include/boost)
include_directories(include/Base Content)
include_directories(include/Contaminants)
include_directories(include/Entities)
include_directories(include/Entities/Enemies)
include_directories(include/Functions)
include_directories(include/Game)
include_directories(include/Graphics)
include_directories(include/Levels)
include_directories(include/Objects)
include_directories(include/Physics)
include_directories(include/Players)
include_directories(include/Projectiles)
include_directories(include/System Tools)
include_directories(include/Tiles)
include_directories(include/Traps)

set(SOURCE_FILES


    data/config.dat
    data/prefix.dat
    data/prefixold.dat
    data/suffix.dat
    data/suffixold.dat
    depend/include/AL/al.h
    depend/include/AL/alc.h
    depend/include/AL/alext.h
    depend/include/AL/efx-creative.h
    depend/include/AL/efx-presets.h
    depend/include/AL/efx.h
    depend/include/GL/internal/dri_interface.h
    depend/include/GL/internal/glcore.h
    depend/include/GL/freeglut.h
    depend/include/GL/freeglut_ext.h
    depend/include/GL/freeglut_std.h
    depend/include/GL/gl.h
    depend/include/GL/gl_mangle.h
    depend/include/GL/glew.h
    depend/include/GL/glext.h
    depend/include/GL/glu.h
    depend/include/GL/glu_mangle.h
    depend/include/GL/glut.h
    depend/include/GL/glx.h
    depend/include/GL/glx_mangle.h
    depend/include/GL/glxew.h
    depend/include/GL/glxext.h
    depend/include/GL/glxint.h
    depend/include/GL/glxmd.h
    depend/include/GL/glxproto.h
    depend/include/GL/glxtokens.h
    depend/include/GL/wglew.h
    depend/include/jpeg/jconfig.h
    depend/include/jpeg/jerror.h
    depend/include/jpeg/jmorecfg.h
    depend/include/jpeg/jpeglib.h
    depend/include/libfreetype/android/freetype/config/ftconfig.h
    depend/include/libfreetype/android/freetype/config/ftheader.h
    depend/include/libfreetype/android/freetype/config/ftmodule.h
    depend/include/libfreetype/android/freetype/config/ftoption.h
    depend/include/libfreetype/android/freetype/config/ftstdlib.h
    depend/include/libfreetype/android/freetype/internal/services/svbdf.h
    depend/include/libfreetype/android/freetype/internal/services/svcid.h
    depend/include/libfreetype/android/freetype/internal/services/svgldict.h
    depend/include/libfreetype/android/freetype/internal/services/svgxval.h
    depend/include/libfreetype/android/freetype/internal/services/svkern.h
    depend/include/libfreetype/android/freetype/internal/services/svmm.h
    depend/include/libfreetype/android/freetype/internal/services/svotval.h
    depend/include/libfreetype/android/freetype/internal/services/svpfr.h
    depend/include/libfreetype/android/freetype/internal/services/svpostnm.h
    depend/include/libfreetype/android/freetype/internal/services/svpscmap.h
    depend/include/libfreetype/android/freetype/internal/services/svpsinfo.h
    depend/include/libfreetype/android/freetype/internal/services/svsfnt.h
    depend/include/libfreetype/android/freetype/internal/services/svttcmap.h
    depend/include/libfreetype/android/freetype/internal/services/svtteng.h
    depend/include/libfreetype/android/freetype/internal/services/svttglyf.h
    depend/include/libfreetype/android/freetype/internal/services/svwinfnt.h
    depend/include/libfreetype/android/freetype/internal/services/svxf86nm.h
    depend/include/libfreetype/android/freetype/internal/autohint.h
    depend/include/libfreetype/android/freetype/internal/ftcalc.h
    depend/include/libfreetype/android/freetype/internal/ftdebug.h
    depend/include/libfreetype/android/freetype/internal/ftdriver.h
    depend/include/libfreetype/android/freetype/internal/ftgloadr.h
    depend/include/libfreetype/android/freetype/internal/ftmemory.h
    depend/include/libfreetype/android/freetype/internal/ftobjs.h
    depend/include/libfreetype/android/freetype/internal/ftpic.h
    depend/include/libfreetype/android/freetype/internal/ftrfork.h
    depend/include/libfreetype/android/freetype/internal/ftserv.h
    depend/include/libfreetype/android/freetype/internal/ftstream.h
    depend/include/libfreetype/android/freetype/internal/fttrace.h
    depend/include/libfreetype/android/freetype/internal/ftvalid.h
    depend/include/libfreetype/android/freetype/internal/internal.h
    depend/include/libfreetype/android/freetype/internal/pcftypes.h
    depend/include/libfreetype/android/freetype/internal/psaux.h
    depend/include/libfreetype/android/freetype/internal/pshints.h
    depend/include/libfreetype/android/freetype/internal/sfnt.h
    depend/include/libfreetype/android/freetype/internal/t1types.h
    depend/include/libfreetype/android/freetype/internal/tttypes.h
    depend/include/libfreetype/android/freetype/freetype.h
    depend/include/libfreetype/android/freetype/ftadvanc.h
    depend/include/libfreetype/android/freetype/ftbbox.h
    depend/include/libfreetype/android/freetype/ftbdf.h
    depend/include/libfreetype/android/freetype/ftbitmap.h
    depend/include/libfreetype/android/freetype/ftcache.h
    depend/include/libfreetype/android/freetype/ftchapters.h
    depend/include/libfreetype/android/freetype/ftcid.h
    depend/include/libfreetype/android/freetype/fterrdef.h
    depend/include/libfreetype/android/freetype/fterrors.h
    depend/include/libfreetype/android/freetype/ftgasp.h
    depend/include/libfreetype/android/freetype/ftglyph.h
    depend/include/libfreetype/android/freetype/ftgxval.h
    depend/include/libfreetype/android/freetype/ftgzip.h
    depend/include/libfreetype/android/freetype/ftimage.h
    depend/include/libfreetype/android/freetype/ftincrem.h
    depend/include/libfreetype/android/freetype/ftlcdfil.h
    depend/include/libfreetype/android/freetype/ftlist.h
    depend/include/libfreetype/android/freetype/ftlzw.h
    depend/include/libfreetype/android/freetype/ftmac.h
    depend/include/libfreetype/android/freetype/ftmm.h
    depend/include/libfreetype/android/freetype/ftmodapi.h
    depend/include/libfreetype/android/freetype/ftmoderr.h
    depend/include/libfreetype/android/freetype/ftotval.h
    depend/include/libfreetype/android/freetype/ftoutln.h
    depend/include/libfreetype/android/freetype/ftpfr.h
    depend/include/libfreetype/android/freetype/ftrender.h
    depend/include/libfreetype/android/freetype/ftsizes.h
    depend/include/libfreetype/android/freetype/ftsnames.h
    depend/include/libfreetype/android/freetype/ftstroke.h
    depend/include/libfreetype/android/freetype/ftsynth.h
    depend/include/libfreetype/android/freetype/ftsystem.h
    depend/include/libfreetype/android/freetype/fttrigon.h
    depend/include/libfreetype/android/freetype/fttypes.h
    depend/include/libfreetype/android/freetype/ftwinfnt.h
    depend/include/libfreetype/android/freetype/ftxf86.h
    depend/include/libfreetype/android/freetype/t1tables.h
    depend/include/libfreetype/android/freetype/ttnameid.h
    depend/include/libfreetype/android/freetype/tttables.h
    depend/include/libfreetype/android/freetype/tttags.h
    depend/include/libfreetype/android/freetype/ttunpat.h
    depend/include/libfreetype/android/ft2build.h
    depend/include/libfreetype/ios/freetype2/freetype/config/ftconfig.h
    depend/include/libfreetype/ios/freetype2/freetype/config/ftheader.h
    depend/include/libfreetype/ios/freetype2/freetype/config/ftmodule.h
    depend/include/libfreetype/ios/freetype2/freetype/config/ftoption.h
    depend/include/libfreetype/ios/freetype2/freetype/config/ftstdlib.h
    depend/include/libfreetype/ios/freetype2/freetype/freetype.h
    depend/include/libfreetype/ios/freetype2/freetype/ftadvanc.h
    depend/include/libfreetype/ios/freetype2/freetype/ftautoh.h
    depend/include/libfreetype/ios/freetype2/freetype/ftbbox.h
    depend/include/libfreetype/ios/freetype2/freetype/ftbdf.h
    depend/include/libfreetype/ios/freetype2/freetype/ftbitmap.h
    depend/include/libfreetype/ios/freetype2/freetype/ftbzip2.h
    depend/include/libfreetype/ios/freetype2/freetype/ftcache.h
    depend/include/libfreetype/ios/freetype2/freetype/ftchapters.h
    depend/include/libfreetype/ios/freetype2/freetype/ftcid.h
    depend/include/libfreetype/ios/freetype2/freetype/fterrdef.h
    depend/include/libfreetype/ios/freetype2/freetype/fterrors.h
    depend/include/libfreetype/ios/freetype2/freetype/ftgasp.h
    depend/include/libfreetype/ios/freetype2/freetype/ftglyph.h
    depend/include/libfreetype/ios/freetype2/freetype/ftgxval.h
    depend/include/libfreetype/ios/freetype2/freetype/ftgzip.h
    depend/include/libfreetype/ios/freetype2/freetype/ftimage.h
    depend/include/libfreetype/ios/freetype2/freetype/ftincrem.h
    depend/include/libfreetype/ios/freetype2/freetype/ftlcdfil.h
    depend/include/libfreetype/ios/freetype2/freetype/ftlist.h
    depend/include/libfreetype/ios/freetype2/freetype/ftlzw.h
    depend/include/libfreetype/ios/freetype2/freetype/ftmac.h
    depend/include/libfreetype/ios/freetype2/freetype/ftmm.h
    depend/include/libfreetype/ios/freetype2/freetype/ftmodapi.h
    depend/include/libfreetype/ios/freetype2/freetype/ftmoderr.h
    depend/include/libfreetype/ios/freetype2/freetype/ftotval.h
    depend/include/libfreetype/ios/freetype2/freetype/ftoutln.h
    depend/include/libfreetype/ios/freetype2/freetype/ftpfr.h
    depend/include/libfreetype/ios/freetype2/freetype/ftrender.h
    depend/include/libfreetype/ios/freetype2/freetype/ftsizes.h
    depend/include/libfreetype/ios/freetype2/freetype/ftsnames.h
    depend/include/libfreetype/ios/freetype2/freetype/ftstroke.h
    depend/include/libfreetype/ios/freetype2/freetype/ftsynth.h
    depend/include/libfreetype/ios/freetype2/freetype/ftsystem.h
    depend/include/libfreetype/ios/freetype2/freetype/fttrigon.h
    depend/include/libfreetype/ios/freetype2/freetype/fttypes.h
    depend/include/libfreetype/ios/freetype2/freetype/ftwinfnt.h
    depend/include/libfreetype/ios/freetype2/freetype/ftxf86.h
    depend/include/libfreetype/ios/freetype2/freetype/t1tables.h
    depend/include/libfreetype/ios/freetype2/freetype/ttnameid.h
    depend/include/libfreetype/ios/freetype2/freetype/tttables.h
    depend/include/libfreetype/ios/freetype2/freetype/tttags.h
    depend/include/libfreetype/ios/freetype2/freetype/ttunpat.h
    depend/include/libfreetype/ios/ft2build.h
    depend/include/libfreetype/osx/freetype2/freetype/config/ftconfig.h
    depend/include/libfreetype/osx/freetype2/freetype/config/ftheader.h
    depend/include/libfreetype/osx/freetype2/freetype/config/ftmodule.h
    depend/include/libfreetype/osx/freetype2/freetype/config/ftoption.h
    depend/include/libfreetype/osx/freetype2/freetype/config/ftstdlib.h
    depend/include/libfreetype/osx/freetype2/freetype/freetype.h
    depend/include/libfreetype/osx/freetype2/freetype/ftadvanc.h
    depend/include/libfreetype/osx/freetype2/freetype/ftautoh.h
    depend/include/libfreetype/osx/freetype2/freetype/ftbbox.h
    depend/include/libfreetype/osx/freetype2/freetype/ftbdf.h
    depend/include/libfreetype/osx/freetype2/freetype/ftbitmap.h
    depend/include/libfreetype/osx/freetype2/freetype/ftbzip2.h
    depend/include/libfreetype/osx/freetype2/freetype/ftcache.h
    depend/include/libfreetype/osx/freetype2/freetype/ftchapters.h
    depend/include/libfreetype/osx/freetype2/freetype/ftcid.h
    depend/include/libfreetype/osx/freetype2/freetype/fterrdef.h
    depend/include/libfreetype/osx/freetype2/freetype/fterrors.h
    depend/include/libfreetype/osx/freetype2/freetype/ftgasp.h
    depend/include/libfreetype/osx/freetype2/freetype/ftglyph.h
    depend/include/libfreetype/osx/freetype2/freetype/ftgxval.h
    depend/include/libfreetype/osx/freetype2/freetype/ftgzip.h
    depend/include/libfreetype/osx/freetype2/freetype/ftimage.h
    depend/include/libfreetype/osx/freetype2/freetype/ftincrem.h
    depend/include/libfreetype/osx/freetype2/freetype/ftlcdfil.h
    depend/include/libfreetype/osx/freetype2/freetype/ftlist.h
    depend/include/libfreetype/osx/freetype2/freetype/ftlzw.h
    depend/include/libfreetype/osx/freetype2/freetype/ftmac.h
    depend/include/libfreetype/osx/freetype2/freetype/ftmm.h
    depend/include/libfreetype/osx/freetype2/freetype/ftmodapi.h
    depend/include/libfreetype/osx/freetype2/freetype/ftmoderr.h
    depend/include/libfreetype/osx/freetype2/freetype/ftotval.h
    depend/include/libfreetype/osx/freetype2/freetype/ftoutln.h
    depend/include/libfreetype/osx/freetype2/freetype/ftpfr.h
    depend/include/libfreetype/osx/freetype2/freetype/ftrender.h
    depend/include/libfreetype/osx/freetype2/freetype/ftsizes.h
    depend/include/libfreetype/osx/freetype2/freetype/ftsnames.h
    depend/include/libfreetype/osx/freetype2/freetype/ftstroke.h
    depend/include/libfreetype/osx/freetype2/freetype/ftsynth.h
    depend/include/libfreetype/osx/freetype2/freetype/ftsystem.h
    depend/include/libfreetype/osx/freetype2/freetype/fttrigon.h
    depend/include/libfreetype/osx/freetype2/freetype/fttypes.h
    depend/include/libfreetype/osx/freetype2/freetype/ftwinfnt.h
    depend/include/libfreetype/osx/freetype2/freetype/ftxf86.h
    depend/include/libfreetype/osx/freetype2/freetype/t1tables.h
    depend/include/libfreetype/osx/freetype2/freetype/ttnameid.h
    depend/include/libfreetype/osx/freetype2/freetype/tttables.h
    depend/include/libfreetype/osx/freetype2/freetype/tttags.h
    depend/include/libfreetype/osx/freetype2/freetype/ttunpat.h
    depend/include/libfreetype/osx/ft2build.h
    depend/include/libfreetype/windows/freetype/config/ftconfig.h
    depend/include/libfreetype/windows/freetype/config/ftheader.h
    depend/include/libfreetype/windows/freetype/config/ftmodule.h
    depend/include/libfreetype/windows/freetype/config/ftoption.h
    depend/include/libfreetype/windows/freetype/config/ftstdlib.h
    depend/include/libfreetype/windows/freetype/internal/internal.h
    depend/include/libfreetype/windows/freetype/freetype.h
    depend/include/libfreetype/windows/freetype/ftbitmap.h
    depend/include/libfreetype/windows/freetype/fterrdef.h
    depend/include/libfreetype/windows/freetype/fterrors.h
    depend/include/libfreetype/windows/freetype/ftglyph.h
    depend/include/libfreetype/windows/freetype/ftimage.h
    depend/include/libfreetype/windows/freetype/ftmoderr.h
    depend/include/libfreetype/windows/freetype/ftoutln.h
    depend/include/libfreetype/windows/freetype/ftsystem.h
    depend/include/libfreetype/windows/freetype/fttypes.h
    depend/include/libfreetype/windows/ft2build.h
    depend/include/libsndfile/android/sndfile.h
    depend/include/libsndfile/osx/sndfile.h
    depend/include/libsndfile/windows/sndfile.h
    depend/include/SFML/Audio/AlResource.hpp
    depend/include/SFML/Audio/Export.hpp
    depend/include/SFML/Audio/Listener.hpp
    depend/include/SFML/Audio/Music.hpp
    depend/include/SFML/Audio/Sound.hpp
    depend/include/SFML/Audio/SoundBuffer.hpp
    depend/include/SFML/Audio/SoundBufferRecorder.hpp
    depend/include/SFML/Audio/SoundRecorder.hpp
    depend/include/SFML/Audio/SoundSource.hpp
    depend/include/SFML/Audio/SoundStream.hpp
    depend/include/SFML/Graphics/BlendMode.hpp
    depend/include/SFML/Graphics/CircleShape.hpp
    depend/include/SFML/Graphics/Color.hpp
    depend/include/SFML/Graphics/ConvexShape.hpp
    depend/include/SFML/Graphics/Drawable.hpp
    depend/include/SFML/Graphics/Export.hpp
    depend/include/SFML/Graphics/Font.hpp
    depend/include/SFML/Graphics/Glyph.hpp
    depend/include/SFML/Graphics/Image.hpp
    depend/include/SFML/Graphics/PrimitiveType.hpp
    depend/include/SFML/Graphics/Rect.hpp
    depend/include/SFML/Graphics/RectangleShape.hpp
    depend/include/SFML/Graphics/RenderStates.hpp
    depend/include/SFML/Graphics/RenderTarget.hpp
    depend/include/SFML/Graphics/RenderTexture.hpp
    depend/include/SFML/Graphics/RenderWindow.hpp
    depend/include/SFML/Graphics/Shader.hpp
    depend/include/SFML/Graphics/Shape.hpp
    depend/include/SFML/Graphics/Sprite.hpp
    depend/include/SFML/Graphics/Text.hpp
    depend/include/SFML/Graphics/Texture.hpp
    depend/include/SFML/Graphics/Transform.hpp
    depend/include/SFML/Graphics/Transformable.hpp
    depend/include/SFML/Graphics/Vertex.hpp
    depend/include/SFML/Graphics/VertexArray.hpp
    depend/include/SFML/Graphics/View.hpp
    depend/include/SFML/Network/Export.hpp
    depend/include/SFML/Network/Ftp.hpp
    depend/include/SFML/Network/Http.hpp
    depend/include/SFML/Network/IpAddress.hpp
    depend/include/SFML/Network/Packet.hpp
    depend/include/SFML/Network/Socket.hpp
    depend/include/SFML/Network/SocketHandle.hpp
    depend/include/SFML/Network/SocketSelector.hpp
    depend/include/SFML/Network/TcpListener.hpp
    depend/include/SFML/Network/TcpSocket.hpp
    depend/include/SFML/Network/UdpSocket.hpp
    depend/include/SFML/System/Clock.hpp
    depend/include/SFML/System/Err.hpp
    depend/include/SFML/System/Export.hpp
    depend/include/SFML/System/InputStream.hpp
    depend/include/SFML/System/Lock.hpp
    depend/include/SFML/System/Mutex.hpp
    depend/include/SFML/System/NonCopyable.hpp
    depend/include/SFML/System/Sleep.hpp
    depend/include/SFML/System/String.hpp
    depend/include/SFML/System/Thread.hpp
    depend/include/SFML/System/ThreadLocal.hpp
    depend/include/SFML/System/ThreadLocalPtr.hpp
    depend/include/SFML/System/Time.hpp
    depend/include/SFML/System/Utf.hpp
    depend/include/SFML/System/Vector2.hpp
    depend/include/SFML/System/Vector3.hpp
    depend/include/SFML/Window/Context.hpp
    depend/include/SFML/Window/ContextSettings.hpp
    depend/include/SFML/Window/Event.hpp
    depend/include/SFML/Window/Export.hpp
    depend/include/SFML/Window/GlResource.hpp
    depend/include/SFML/Window/Joystick.hpp
    depend/include/SFML/Window/Keyboard.hpp
    depend/include/SFML/Window/Mouse.hpp
    depend/include/SFML/Window/Sensor.hpp
    depend/include/SFML/Window/Touch.hpp
    depend/include/SFML/Window/VideoMode.hpp
    depend/include/SFML/Window/Window.hpp
    depend/include/SFML/Window/WindowHandle.hpp
    depend/include/SFML/Window/WindowStyle.hpp
    depend/include/SFML/Audio.hpp
    depend/include/SFML/Config.hpp
    depend/include/SFML/Graphics.hpp
    depend/include/SFML/Main.hpp
    depend/include/SFML/Network.hpp
    depend/include/SFML/OpenGL.hpp
    depend/include/SFML/System.hpp
    depend/include/SFML/Window.hpp
    depend/include/xcb/bigreq.h
    depend/include/xcb/glx.h
    depend/include/xcb/randr.h
    depend/include/xcb/render.h
    depend/include/xcb/shm.h
    depend/include/xcb/xc_misc.h
    depend/include/xcb/xcb.h
    depend/include/xcb/xcb_atom.h
    depend/include/xcb/xcb_aux.h
    depend/include/xcb/xcb_bitops.h
    depend/include/xcb/xcb_event.h
    depend/include/xcb/xcb_ewmh.h
    depend/include/xcb/xcb_icccm.h
    depend/include/xcb/xcb_image.h
    depend/include/xcb/xcb_pixel.h
    depend/include/xcb/xcb_renderutil.h
    depend/include/xcb/xcb_util.h
    depend/include/xcb/xcbext.h
    depend/include/xcb/xproto.h
    depend/include/_G_config.h
    depend/include/a.out.h
    depend/include/aio.h
    depend/include/aliases.h
    depend/include/alloca.h
    depend/include/ar.h
    depend/include/argp.h
    depend/include/argz.h
    depend/include/assert.h
    depend/include/autosprintf.h
    depend/include/byteswap.h
    depend/include/clif.h
    depend/include/complex.h
    depend/include/cpio.h
    depend/include/crypt.h
    depend/include/ctype.h
    depend/include/dirent.h
    depend/include/dlfcn.h
    depend/include/elf.h
    depend/include/endian.h
    depend/include/envz.h
    depend/include/err.h
    depend/include/errno.h
    depend/include/error.h
    depend/include/execinfo.h
    depend/include/fcntl.h
    depend/include/features.h
    depend/include/fenv.h
    depend/include/fmtmsg.h
    depend/include/fnmatch.h
    depend/include/fstab.h
    depend/include/ft2build.h
    depend/include/fts.h
    depend/include/ftw.h
    depend/include/gconv.h
    depend/include/getopt.h
    depend/include/gettext-po.h
    depend/include/glob.h
    depend/include/gnu-versions.h
    depend/include/grp.h
    depend/include/gshadow.h
    depend/include/iconv.h
    depend/include/ieee754.h
    depend/include/ifaddrs.h
    depend/include/inttypes.h
    depend/include/jerror.h
    depend/include/jmorecfg.h
    depend/include/jpegint.h
    depend/include/jpeglib.h
    depend/include/langinfo.h
    depend/include/lastlog.h
    depend/include/libgen.h
    depend/include/libintl.h
    depend/include/libio.h
    depend/include/libudev.h
    depend/include/limits.h
    depend/include/link.h
    depend/include/locale.h
    depend/include/malloc.h
    depend/include/math.h
    depend/include/mcheck.h
    depend/include/memory.h
    depend/include/mntent.h
    depend/include/monetary.h
    depend/include/mqueue.h
    depend/include/netdb.h
    depend/include/nl_types.h
    depend/include/nss.h
    depend/include/obstack.h
    depend/include/paths.h
    depend/include/poll.h
    depend/include/printf.h
    depend/include/pthread.h
    depend/include/pty.h
    depend/include/pwd.h
    depend/include/re_comp.h
    depend/include/regex.h
    depend/include/regexp.h
    depend/include/resolv.h
    depend/include/rr.h
    depend/include/rrtransport.h
    depend/include/sched.h
    depend/include/search.h
    depend/include/semaphore.h
    depend/include/setjmp.h
    depend/include/sgtty.h
    depend/include/shadow.h
    depend/include/signal.h
    depend/include/sndfile.h
    depend/include/sndfile.hh
    depend/include/spawn.h
    depend/include/stab.h
    depend/include/stdint.h
    depend/include/stdio.h
    depend/include/stdio_ext.h
    depend/include/stdlib.h
    depend/include/string.h
    depend/include/strings.h
    depend/include/stropts.h
    depend/include/sudo_plugin.h
    depend/include/syscall.h
    depend/include/sysexits.h
    depend/include/syslog.h
    depend/include/tar.h
    depend/include/termio.h
    depend/include/termios.h
    depend/include/tgmath.h
    depend/include/thread_db.h
    depend/include/time.h
    depend/include/ttyent.h
    depend/include/turbojpeg.h
    depend/include/ucontext.h
    depend/include/ulimit.h
    depend/include/unistd.h
    depend/include/ustat.h
    depend/include/utime.h
    depend/include/utmp.h
    depend/include/utmpx.h
    depend/include/values.h
    depend/include/wait.h
    depend/include/wchar.h
    depend/include/wctype.h
    depend/include/wordexp.h
    depend/include/xf86drm.h
    depend/include/xf86drmMode.h
    depend/include/xlocale.h
    depend/include/zconf.h
    depend/include/zlib.h
    depend/include/zlibdefs.h
    "include/Base Content/content.h"
    "include/Base Content/dynamiccontent.h"
    "include/Base Content/nullcontent.h"
    "include/Base Content/passivecontent.h"
    "include/Base Content/staticcontent.h"
    "include/Collective Headers/allcontenttypes.h"
    include/Contaminants/contaminant.h
    include/Entities/Enemies/enemy.h
    include/Entities/Enemies/gelatinouscube.h
    include/Entities/entity.h
    include/Functions/debugtools.h
    include/Functions/fastmaths.h
    include/Game/game.h
    include/Graphics/animation.h
    include/Graphics/filmreel.h
    include/Graphics/layeredanimation.h
    include/Levels/contentbuffer.h
    include/Levels/dungeon.h
    include/Levels/room.h
    include/Objects/Containers/chest.h
    include/Objects/Containers/container.h
    include/Objects/Containers/pot.h
    "include/Objects/Physics Objects/bomb.h"
    "include/Objects/Physics Objects/football.h"
    include/Objects/Pickups/key.h
    include/Objects/Pickups/pickup.h
    "include/Objects/Static Blocks/cauldron.h"
    include/Objects/Weapons/Axes/baseaxe.h
    include/Objects/Weapons/axe.h
    include/Objects/Weapons/weapon.h
    include/Objects/gameobject.h
    include/Objects/horizdoor.h
    include/Objects/immortalbox.h
    include/Objects/verticdoor.h
    include/Physics/Particles/riser.h
    include/Physics/Particles/trail.h
    "include/Physics/Physics Events/explosion.h"
    "include/Physics/Physics Events/physicsevent.h"
    include/Physics/blankhitbox.h
    include/Physics/circularhitbox.h
    include/Physics/compoundhitbox.h
    include/Physics/destructable.h
    include/Physics/hitbox.h
    include/Physics/multiemitter.h
    include/Physics/particle.h
    include/Physics/particleemitter.h
    include/Physics/physicsengine.h
    include/Physics/ray.h
    include/Physics/raygun.h
    include/Physics/rectangularhitbox.h
    include/Players/player.h
    include/Projectiles/projectile.h
    "include/System Tools/chunk.h"
    "include/System Tools/contentmanager.h"
    "include/System Tools/debugdisplay.h"
    "include/System Tools/event.h"
    "include/System Tools/eventhandler.h"
    "include/System Tools/menu.h"
    "include/System Tools/menuitem.h"
    "include/System Tools/renderengine.h"
    "include/System Tools/resourcemanager.h"
    "include/System Tools/stringtools.h"
    "include/System Tools/windowconfig.h"
    include/Tiles/doortile.h
    include/Tiles/floor.h
    include/Tiles/metatile.h
    include/Tiles/solidblock.h
    include/Tiles/tile.h
    include/Tiles/voidtile.h
    include/Tiles/wall.h
    include/Traps/trap.h
    include/Traps/verticalarrowtrap.h
    "src/Base Content/content.cpp"
    "src/Base Content/dynamiccontent.cpp"
    "src/Base Content/nullcontent.cpp"
    "src/Base Content/passivecontent.cpp"
    "src/Base Content/staticcontent.cpp"
    src/Contaminants/contaminant.cpp
    src/Entities/Enemies/enemy.cpp
    src/Entities/Enemies/gelatinouscube.cpp
    src/Entities/entity.cpp
    src/Functions/debugtools.cpp
    src/Functions/fastmaths.cpp
    src/Game/game.cpp
    src/Graphics/animation.cpp
    src/Graphics/filmreel.cpp
    src/Graphics/layeredanimation.cpp
    src/Levels/Management/contentbuffer.cpp
    src/Levels/dungeon.cpp
    src/Levels/room.cpp
    src/Objects/Containers/chest.cpp
    src/Objects/Containers/container.cpp
    src/Objects/Containers/pot.cpp
    "src/Objects/Physics Objects/bomb.cpp"
    "src/Objects/Physics Objects/football.cpp"
    src/Objects/Pickups/key.cpp
    src/Objects/Pickups/pickup.cpp
    "src/Objects/Static Blocks/cauldron.cpp"
    src/Objects/Weapons/Axes/baseaxe.cpp
    src/Objects/Weapons/axe.cpp
    src/Objects/Weapons/weapon.cpp
    src/Objects/gameobject.cpp
    src/Objects/horizdoor.cpp
    src/Objects/immortalbox.cpp
    src/Objects/verticdoor.cpp
    src/Physics/Particles/riser.cpp
    src/Physics/Particles/trail.cpp
    "src/Physics/Physics Events/explosion.cpp"
    "src/Physics/Physics Events/physicsevent.cpp"
    src/Physics/blankhitbox.cpp
    src/Physics/circularhitbox.cpp
    src/Physics/compoundhitbox.cpp
    src/Physics/destructable.cpp
    src/Physics/hitbox.cpp
    src/Physics/multiemitter.cpp
    src/Physics/particle.cpp
    src/Physics/particleemitter.cpp
    src/Physics/physicsengine.cpp
    src/Physics/ray.cpp
    src/Physics/raygun.cpp
    src/Physics/rectangularhitbox.cpp
    src/Players/player.cpp
    src/Projectiles/projectile.cpp
    "src/System Tools/button.cpp"
    "src/System Tools/chunk.cpp"
    "src/System Tools/contentmanager.cpp"
    "src/System Tools/debugdisplay.cpp"
    "src/System Tools/event.cpp"
    "src/System Tools/eventhandler.cpp"
    "src/System Tools/keymap.cpp"
    "src/System Tools/menu.cpp"
    "src/System Tools/menuitem.cpp"
    "src/System Tools/renderengine.cpp"
    "src/System Tools/resourcemanager.cpp"
    "src/System Tools/slider.cpp"
    "src/System Tools/stringtools.cpp"
    "src/System Tools/windowconfig.cpp"
    src/Tiles/doortile.cpp
    src/Tiles/floor.cpp
    src/Tiles/metatile.cpp
    src/Tiles/solidblock.cpp
    src/Tiles/tile.cpp
    src/Tiles/voidtile.cpp
    src/Tiles/wall.cpp
    src/Traps/trap.cpp
    src/Traps/verticalarrowtrap.cpp

    main.cpp)

set(EXECUTABLE_NAME "BarbarianQuestII")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} include/Entities/entities.h include/Entities/Enemies/enemies.h include/Objects/objects.h include/Tiles/tiles.h include/Traps/traps.h include/Objects/Weapons/weapons.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
