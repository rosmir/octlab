<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="9008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="OCTLab.lvlib" Type="Library" URL="/&lt;userlib&gt;/OCTLab/OCTLab.lvlib"/>
		<Item Name="COPYRIGHT.TXT" Type="Document" URL="../../dll/COPYRIGHT.TXT"/>
		<Item Name="libfftw3-3.dll" Type="Document" URL="../../dll/libfftw3-3.dll"/>
		<Item Name="License.rtf" Type="Document" URL="../../dll/License.rtf"/>
		<Item Name="OCTLib.dll" Type="Document" URL="../../dll/OCTLib.dll"/>
		<Item Name="README.TXT" Type="Document" URL="../../dll/README.TXT"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
			</Item>
			<Item Name="user.lib" Type="Folder">
				<Item Name="OL_Engine_Austin_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Austin_Alazar.vi"/>
				<Item Name="OL_lin_int_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_dbl.vi"/>
				<Item Name="OL_lin_int_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_i16.vi"/>
				<Item Name="OL_lin_int_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_i32.vi"/>
				<Item Name="OL_lin_int_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_sgl.vi"/>
				<Item Name="OL_lin_int_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_u16.vi"/>
				<Item Name="OL_lin_int_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_u32.vi"/>
				<Item Name="OL_lin_int_fft_u8.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_u8.vi"/>
				<Item Name="OL_lin_int_fft_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_lin_int_fft_Alazar.vi"/>
				<Item Name="OL_phase_calibration.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_analysis.llb/OL_phase_calibration.vi"/>
				<Item Name="OL_simple_threshold2.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_analysis.llb/OL_simple_threshold2.vi"/>
				<Item Name="OL_simple_Doppler_filtered.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_analysis.llb/OL_simple_Doppler_filtered.vi"/>
				<Item Name="OL_Doppler_filtered.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_analysis.llb/OL_Doppler_filtered.vi"/>
				<Item Name="OL_variance_map_filtered.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_speckle.llb/OL_variance_map_filtered.vi"/>
				<Item Name="OL_contrast_map_filtered.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_speckle.llb/OL_contrast_map_filtered.vi"/>
				<Item Name="OL_Engine_Austin_I16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Austin_I16.vi"/>
				<Item Name="OL_Engine_Austin_U16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Austin_U16.vi"/>
				<Item Name="OL_Engine_Austin_U8.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Austin_U8.vi"/>
				<Item Name="OL_Engine_Houston_I16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Houston_I16.vi"/>
				<Item Name="OL_simple_lin_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_dbl.vi"/>
				<Item Name="OL_simple_lin_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_i16.vi"/>
				<Item Name="OL_simple_lin_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_i32.vi"/>
				<Item Name="OL_simple_lin_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_sgl.vi"/>
				<Item Name="OL_simple_lin_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_u16.vi"/>
				<Item Name="OL_simple_lin_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_u32.vi"/>
				<Item Name="OL_simple_lin_fft_u8.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_u8.vi"/>
				<Item Name="OL_simple_lin_fft_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_lin_fft_Alazar.vi"/>
				<Item Name="OL_Engine_Houston_U16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Houston_U16.vi"/>
				<Item Name="OL_Engine_Houston_U8.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Houston_U8.vi"/>
				<Item Name="OL_Engine_Houston_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OL_Engines.llb/OL_Engine_Houston_Alazar.vi"/>
				<Item Name="OL_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_dbl.vi"/>
				<Item Name="OL_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_i16.vi"/>
				<Item Name="OL_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_i32.vi"/>
				<Item Name="OL_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_sgl.vi"/>
				<Item Name="OL_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_u16.vi"/>
				<Item Name="OL_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_fft_u32.vi"/>
				<Item Name="OL_mzi_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_dbl.vi"/>
				<Item Name="OL_mzi_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_i16.vi"/>
				<Item Name="OL_mzi_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_i32.vi"/>
				<Item Name="OL_mzi_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_sgl.vi"/>
				<Item Name="OL_mzi_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_u16.vi"/>
				<Item Name="OL_mzi_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_u32.vi"/>
				<Item Name="OL_mzi_fft_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_mzi_fft_Alazar.vi"/>
				<Item Name="OL_simple_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_dbl.vi"/>
				<Item Name="OL_simple_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_i16.vi"/>
				<Item Name="OL_simple_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_i32.vi"/>
				<Item Name="OL_simple_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_sgl.vi"/>
				<Item Name="OL_simple_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_u16.vi"/>
				<Item Name="OL_simple_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_fft_u32.vi"/>
				<Item Name="OL_simple_mzi_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_dbl.vi"/>
				<Item Name="OL_simple_mzi_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_i16.vi"/>
				<Item Name="OL_simple_mzi_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_i32.vi"/>
				<Item Name="OL_simple_mzi_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_sgl.vi"/>
				<Item Name="OL_simple_mzi_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_u16.vi"/>
				<Item Name="OL_simple_mzi_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_u32.vi"/>
				<Item Name="OL_simple_mzi_fft_Alazar.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_simple_mzi_fft_Alazar.vi"/>
				<Item Name="OL_spline_fft_dbl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_dbl.vi"/>
				<Item Name="OL_spline_fft_i16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_i16.vi"/>
				<Item Name="OL_spline_fft_i32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_i32.vi"/>
				<Item Name="OL_spline_fft_sgl.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_sgl.vi"/>
				<Item Name="OL_spline_fft_u16.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_u16.vi"/>
				<Item Name="OL_spline_fft_u32.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_u32.vi"/>
				<Item Name="OL_spline_fft_u8.vi" Type="VI" URL="/&lt;userlib&gt;/OCTLab/OCTLab.llb/OL_spline_fft_u8.vi"/>
			</Item>
			<Item Name="OCTLib.dll" Type="Document" URL="OCTLib.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="OCTLab Installer" Type="Installer">
				<Property Name="arpCompany" Type="Str">OCTLab Project</Property>
				<Property Name="arpContact" Type="Str">Stepan Baranov (email: stepan@baranov.su)</Property>
				<Property Name="arpURL" Type="Str">http://OCTLab.GoogleCode.com/</Property>
				<Property Name="BldInfo.Count" Type="Int">5</Property>
				<Property Name="BldInfo[0].Dir" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="BldInfo[0].Tag" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="BldInfo[1].Dir" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="BldInfo[1].Tag" Type="Ref">/My Computer/OCTLib.dll</Property>
				<Property Name="BldInfo[2].Dir" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="BldInfo[2].Tag" Type="Ref">/My Computer/libfftw3-3.dll</Property>
				<Property Name="BldInfo[3].Dir" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="BldInfo[3].Tag" Type="Ref">/My Computer/COPYRIGHT.TXT</Property>
				<Property Name="BldInfo[4].Dir" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="BldInfo[4].Tag" Type="Ref">/My Computer/README.TXT</Property>
				<Property Name="BuildLabel" Type="Str">OCTLab Installer</Property>
				<Property Name="BuildLocation" Type="Path">../../builds/OCTLab/OCTLab Installer</Property>
				<Property Name="DirInfo.Count" Type="Int">2</Property>
				<Property Name="DirInfo.DefaultDir" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="DirInfo[0].DirName" Type="Str">user.lib</Property>
				<Property Name="DirInfo[0].DirTag" Type="Str">{DD37ED02-6A4D-4716-827A-19447691635A}</Property>
				<Property Name="DirInfo[0].ParentTag" Type="Str">{67E763D4-AC4D-482B-9145-4986F20987C5}</Property>
				<Property Name="DirInfo[1].DirName" Type="Str">OCTLab</Property>
				<Property Name="DirInfo[1].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="DirInfo[1].ParentTag" Type="Str">{DD37ED02-6A4D-4716-827A-19447691635A}</Property>
				<Property Name="DistID" Type="Str">{BFE8CA6B-0777-473B-8FEB-19F1C911F735}</Property>
				<Property Name="FileInfo.Count" Type="Int">24</Property>
				<Property Name="FileInfo[0].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[0].FileName" Type="Str">OCTLab.lvlib</Property>
				<Property Name="FileInfo[0].FileTag" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[0].Type" Type="Int">4</Property>
				<Property Name="FileInfo[0].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[1].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[1].FileName" Type="Str">COPYRIGHT.TXT</Property>
				<Property Name="FileInfo[1].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/COPYRIGHT.TXT</Property>
				<Property Name="FileInfo[1].Type" Type="Int">4</Property>
				<Property Name="FileInfo[1].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[10].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[10].FileName" Type="Str">OL_Engines.llb</Property>
				<Property Name="FileInfo[10].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_Engines.llb</Property>
				<Property Name="FileInfo[10].Type" Type="Int">4</Property>
				<Property Name="FileInfo[10].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[11].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[11].FileName" Type="Str">OL_FFT.vi</Property>
				<Property Name="FileInfo[11].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_FFT.vi</Property>
				<Property Name="FileInfo[11].Type" Type="Int">4</Property>
				<Property Name="FileInfo[11].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[12].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[12].FileName" Type="Str">OL_lin_int_FFT.vi</Property>
				<Property Name="FileInfo[12].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_lin_int_FFT.vi</Property>
				<Property Name="FileInfo[12].Type" Type="Int">4</Property>
				<Property Name="FileInfo[12].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[13].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[13].FileName" Type="Str">OL_MZI_FFT.vi</Property>
				<Property Name="FileInfo[13].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_MZI_FFT.vi</Property>
				<Property Name="FileInfo[13].Type" Type="Int">4</Property>
				<Property Name="FileInfo[13].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[14].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[14].FileName" Type="Str">OL_simple_FFT.vi</Property>
				<Property Name="FileInfo[14].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_simple_FFT.vi</Property>
				<Property Name="FileInfo[14].Type" Type="Int">4</Property>
				<Property Name="FileInfo[14].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[15].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[15].FileName" Type="Str">OL_simple_lin_FFT.vi</Property>
				<Property Name="FileInfo[15].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_simple_lin_FFT.vi</Property>
				<Property Name="FileInfo[15].Type" Type="Int">4</Property>
				<Property Name="FileInfo[15].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[16].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[16].FileName" Type="Str">OL_simple_MZI_FFT.vi</Property>
				<Property Name="FileInfo[16].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_simple_MZI_FFT.vi</Property>
				<Property Name="FileInfo[16].Type" Type="Int">4</Property>
				<Property Name="FileInfo[16].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[17].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[17].FileName" Type="Str">OL_speckle.llb</Property>
				<Property Name="FileInfo[17].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_speckle.llb</Property>
				<Property Name="FileInfo[17].Type" Type="Int">4</Property>
				<Property Name="FileInfo[17].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[18].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[18].FileName" Type="Str">OL_spline_FFT.vi</Property>
				<Property Name="FileInfo[18].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_spline_FFT.vi</Property>
				<Property Name="FileInfo[18].Type" Type="Int">4</Property>
				<Property Name="FileInfo[18].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[19].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[19].FileName" Type="Str">README.TXT</Property>
				<Property Name="FileInfo[19].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/README.TXT</Property>
				<Property Name="FileInfo[19].Type" Type="Int">4</Property>
				<Property Name="FileInfo[19].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[2].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[2].FileName" Type="Str">dir.mnu</Property>
				<Property Name="FileInfo[2].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/dir.mnu</Property>
				<Property Name="FileInfo[2].Type" Type="Int">4</Property>
				<Property Name="FileInfo[2].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[20].DirTag" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="FileInfo[20].FileTag" Type="Ref">/My Computer/OCTLib.dll</Property>
				<Property Name="FileInfo[21].DirTag" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="FileInfo[21].FileTag" Type="Ref">/My Computer/libfftw3-3.dll</Property>
				<Property Name="FileInfo[22].DirTag" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="FileInfo[22].FileTag" Type="Ref">/My Computer/COPYRIGHT.TXT</Property>
				<Property Name="FileInfo[23].DirTag" Type="Str">{D2272923-C63E-4A06-9729-85B1AD1CFB2A}</Property>
				<Property Name="FileInfo[23].FileTag" Type="Ref">/My Computer/README.TXT</Property>
				<Property Name="FileInfo[3].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[3].FileName" Type="Str">LV_FFT.vi</Property>
				<Property Name="FileInfo[3].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/LV_FFT.vi</Property>
				<Property Name="FileInfo[3].Type" Type="Int">4</Property>
				<Property Name="FileInfo[3].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[4].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[4].FileName" Type="Str">OCTLab.llb</Property>
				<Property Name="FileInfo[4].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OCTLab.llb</Property>
				<Property Name="FileInfo[4].Type" Type="Int">4</Property>
				<Property Name="FileInfo[4].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[5].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[5].FileName" Type="Str">OCTLibVer.vi</Property>
				<Property Name="FileInfo[5].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OCTLibVer.vi</Property>
				<Property Name="FileInfo[5].Type" Type="Int">4</Property>
				<Property Name="FileInfo[5].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[6].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[6].FileName" Type="Str">OL_analysis.llb</Property>
				<Property Name="FileInfo[6].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_analysis.llb</Property>
				<Property Name="FileInfo[6].Type" Type="Int">4</Property>
				<Property Name="FileInfo[6].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[7].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[7].FileName" Type="Str">OL_config.llb</Property>
				<Property Name="FileInfo[7].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_config.llb</Property>
				<Property Name="FileInfo[7].Type" Type="Int">4</Property>
				<Property Name="FileInfo[7].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[8].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[8].FileName" Type="Str">OL_Engine_Austin.vi</Property>
				<Property Name="FileInfo[8].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_Engine_Austin.vi</Property>
				<Property Name="FileInfo[8].Type" Type="Int">4</Property>
				<Property Name="FileInfo[8].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="FileInfo[9].DirTag" Type="Str">{7F9FCFE5-9D19-48E3-BB4A-3A8BDAB0050E}</Property>
				<Property Name="FileInfo[9].FileName" Type="Str">OL_Engine_Houston.vi</Property>
				<Property Name="FileInfo[9].FileTag" Type="Ref">/My Computer/OCTLab.lvlib/OL_Engine_Houston.vi</Property>
				<Property Name="FileInfo[9].Type" Type="Int">4</Property>
				<Property Name="FileInfo[9].TypeID" Type="Ref">/My Computer/OCTLab.lvlib</Property>
				<Property Name="IncludeError" Type="Bool">false</Property>
				<Property Name="InstSpecVersion" Type="Str">9018011</Property>
				<Property Name="LicenseFile" Type="Ref">/My Computer/License.rtf</Property>
				<Property Name="LV80Higher" Type="Bool">true</Property>
				<Property Name="OSCheck" Type="Int">1</Property>
				<Property Name="OSCheck_Vista" Type="Bool">false</Property>
				<Property Name="ProductName" Type="Str">OCTLab x32</Property>
				<Property Name="ProductVersion" Type="Str">0.8.7</Property>
				<Property Name="ReadmeFile" Type="Ref"></Property>
				<Property Name="UpgradeCode" Type="Str">{3EFC6F01-FD72-4AF0-B338-64ED85F1D180}</Property>
				<Property Name="WindowMessage" Type="Str">C++ and LabView solution for Optical Coherence Tomography</Property>
				<Property Name="WindowTitle" Type="Str">OCTLab x32</Property>
			</Item>
		</Item>
	</Item>
</Project>
