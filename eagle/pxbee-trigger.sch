<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A4L-LOC" urn="urn:adsk.eagle:symbol:13874/1" library_version="1">
<wire x1="256.54" y1="3.81" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="256.54" y1="8.89" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="256.54" y1="13.97" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="256.54" y1="19.05" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="3.81" x2="161.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="24.13" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="215.265" y1="24.13" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="246.38" y1="3.81" x2="246.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="215.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="215.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<text x="217.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="217.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="230.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="216.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A4L-LOC" urn="urn:adsk.eagle:component:13926/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A4L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="parts">
<description>&lt;b&gt;https://eagle.componentsearchengine.com&lt;/b&gt;&lt;p&gt;&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="DIP798W58P510L828H330Q4N">
<description>&lt;b&gt;PDIP4 -11&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="-3.988" y="2.55" drill="0.78" diameter="1.18" shape="square"/>
<pad name="2" x="-3.988" y="-2.55" drill="0.78" diameter="1.18"/>
<pad name="3" x="3.988" y="-2.55" drill="0.78" diameter="1.18"/>
<pad name="4" x="3.988" y="2.55" drill="0.78" diameter="1.18"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-5.125" y1="4.505" x2="5.125" y2="4.505" width="0.05" layer="51"/>
<wire x1="5.125" y1="4.505" x2="5.125" y2="-4.505" width="0.05" layer="51"/>
<wire x1="5.125" y1="-4.505" x2="-5.125" y2="-4.505" width="0.05" layer="51"/>
<wire x1="-5.125" y1="-4.505" x2="-5.125" y2="4.505" width="0.05" layer="51"/>
<wire x1="-3.25" y1="4.255" x2="3.25" y2="4.255" width="0.1" layer="51"/>
<wire x1="3.25" y1="4.255" x2="3.25" y2="-4.255" width="0.1" layer="51"/>
<wire x1="3.25" y1="-4.255" x2="-3.25" y2="-4.255" width="0.1" layer="51"/>
<wire x1="-3.25" y1="-4.255" x2="-3.25" y2="4.255" width="0.1" layer="51"/>
<wire x1="-3.25" y1="1.705" x2="-0.7" y2="4.255" width="0.1" layer="51"/>
<wire x1="-4.578" y1="4.255" x2="3.25" y2="4.255" width="0.2" layer="21"/>
<wire x1="-3.25" y1="-4.255" x2="3.25" y2="-4.255" width="0.2" layer="21"/>
</package>
<package name="MGFS1R52415">
<description>&lt;b&gt;MGFS1R52415&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="-6.4" y="1.14" drill="0.9" diameter="1.4"/>
<pad name="2" x="-3.86" y="1.14" drill="0.9" diameter="1.4"/>
<pad name="3" x="1.22" y="1.14" drill="0.9" diameter="1.4"/>
<pad name="4" x="6.3" y="1.14" drill="0.9" diameter="1.4"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-8.5" y1="3.94" x2="8.5" y2="3.94" width="0.2" layer="51"/>
<wire x1="8.5" y1="3.94" x2="8.5" y2="-3.94" width="0.2" layer="51"/>
<wire x1="8.5" y1="-3.94" x2="-8.5" y2="-3.94" width="0.2" layer="51"/>
<wire x1="-8.5" y1="-3.94" x2="-8.5" y2="3.94" width="0.2" layer="51"/>
<wire x1="-8.5" y1="3.94" x2="8.5" y2="3.94" width="0.1" layer="21"/>
<wire x1="8.5" y1="3.94" x2="8.5" y2="-3.94" width="0.1" layer="21"/>
<wire x1="8.5" y1="-3.94" x2="-8.5" y2="-3.94" width="0.1" layer="21"/>
<wire x1="-8.5" y1="-3.94" x2="-8.5" y2="3.94" width="0.1" layer="21"/>
<wire x1="-9.5" y1="4.94" x2="9.5" y2="4.94" width="0.1" layer="51"/>
<wire x1="9.5" y1="4.94" x2="9.5" y2="-4.94" width="0.1" layer="51"/>
<wire x1="9.5" y1="-4.94" x2="-9.5" y2="-4.94" width="0.1" layer="51"/>
<wire x1="-9.5" y1="-4.94" x2="-9.5" y2="4.94" width="0.1" layer="51"/>
<wire x1="-6.5" y1="4.44" x2="-6.5" y2="4.44" width="0.2" layer="21"/>
<wire x1="-6.5" y1="4.44" x2="-6.3" y2="4.44" width="0.2" layer="21" curve="-180"/>
<wire x1="-6.3" y1="4.44" x2="-6.3" y2="4.44" width="0.2" layer="21"/>
<wire x1="-6.3" y1="4.44" x2="-6.5" y2="4.44" width="0.2" layer="21" curve="-180"/>
</package>
<package name="BC548BTA">
<description>&lt;b&gt;3-Lead TO-92, 0.2 in-line Ammo ver.&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="0.96" diameter="1.493" shape="square"/>
<pad name="2" x="2.6" y="0" drill="0.96" diameter="1.493"/>
<pad name="3" x="5.2" y="0" drill="0.96" diameter="1.493"/>
<text x="2.6" y="0.38" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="2.6" y="0.38" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.747" y1="3.24" x2="6.947" y2="3.24" width="0.1" layer="51"/>
<wire x1="6.947" y1="3.24" x2="6.947" y2="-2.48" width="0.1" layer="51"/>
<wire x1="6.947" y1="-2.48" x2="-1.747" y2="-2.48" width="0.1" layer="51"/>
<wire x1="-1.747" y1="-2.48" x2="-1.747" y2="3.24" width="0.1" layer="51"/>
<wire x1="0.22" y1="-1.48" x2="4.98" y2="-1.48" width="0.2" layer="51"/>
<wire x1="0.1" y1="-0.26" x2="5.1" y2="-0.26" width="0.2" layer="51"/>
<wire x1="5.1" y1="-0.26" x2="5.1" y2="-0.26" width="0.2" layer="51"/>
<wire x1="5.1" y1="-0.26" x2="0.1" y2="-0.26" width="0.2" layer="51" curve="180"/>
<wire x1="0.22" y1="-1.48" x2="0.1" y2="-0.36" width="0.2" layer="51"/>
<wire x1="4.98" y1="-1.48" x2="5.1" y2="-0.26" width="0.2" layer="51"/>
<wire x1="0.2" y1="-1.06" x2="0.22" y2="-1.46" width="0.1" layer="21"/>
<wire x1="0.22" y1="-1.46" x2="5" y2="-1.48" width="0.1" layer="21"/>
<wire x1="5" y1="-1.48" x2="5" y2="-1.06" width="0.1" layer="21"/>
<wire x1="2.4" y1="2.24" x2="2.8" y2="2.24" width="0.1" layer="21"/>
</package>
<package name="APAN3103">
<description>&lt;b&gt;APAN3103-1&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1" diameter="1.5"/>
<pad name="2" x="2.54" y="0" drill="1" diameter="1.5"/>
<pad name="5" x="12.7" y="0" drill="1.2" diameter="1.8"/>
<pad name="6" x="17.78" y="0" drill="1.2" diameter="1.8"/>
<text x="8.88" y="-0.925" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="8.88" y="-0.925" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.12" y1="1.2" x2="18.88" y2="1.2" width="0.2" layer="51"/>
<wire x1="18.88" y1="1.2" x2="18.88" y2="-3.8" width="0.2" layer="51"/>
<wire x1="18.88" y1="-3.8" x2="-1.12" y2="-3.8" width="0.2" layer="51"/>
<wire x1="-1.12" y1="-3.8" x2="-1.12" y2="1.2" width="0.2" layer="51"/>
<wire x1="18.88" y1="1.2" x2="-1.12" y2="1.2" width="0.1" layer="21"/>
<wire x1="-1.12" y1="1.2" x2="-1.12" y2="-3.8" width="0.1" layer="21"/>
<wire x1="-1.12" y1="-3.8" x2="18.88" y2="-3.8" width="0.1" layer="21"/>
<wire x1="18.88" y1="-3.8" x2="18.88" y2="1.2" width="0.1" layer="21"/>
<wire x1="-2.12" y1="-4.8" x2="19.88" y2="-4.8" width="0.1" layer="51"/>
<wire x1="19.88" y1="-4.8" x2="19.88" y2="2.95" width="0.1" layer="51"/>
<wire x1="19.88" y1="2.95" x2="-2.12" y2="2.95" width="0.1" layer="51"/>
<wire x1="-2.12" y1="2.95" x2="-2.12" y2="-4.8" width="0.1" layer="51"/>
<wire x1="-0.2" y1="1.9" x2="-0.2" y2="1.9" width="0.2" layer="21"/>
<wire x1="-0.2" y1="1.9" x2="-0.1" y2="1.9" width="0.2" layer="21" curve="180"/>
<wire x1="-0.1" y1="1.9" x2="-0.1" y2="1.9" width="0.2" layer="21"/>
<wire x1="-0.1" y1="1.9" x2="-0.2" y2="1.9" width="0.2" layer="21" curve="180"/>
<wire x1="-0.2" y1="1.9" x2="-0.2" y2="1.9" width="0.2" layer="21"/>
<wire x1="-0.2" y1="1.9" x2="-0.1" y2="1.9" width="0.2" layer="21" curve="180"/>
</package>
<package name="DIOAD1405W86L465D235">
<description>&lt;b&gt;AXIAL-LEAD-CASE 59-10&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1.05" diameter="1.575" shape="square"/>
<pad name="2" x="14.1" y="0" drill="1.05" diameter="1.575"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.038" y1="1.525" x2="15.137" y2="1.525" width="0.05" layer="51"/>
<wire x1="15.137" y1="1.525" x2="15.137" y2="-1.525" width="0.05" layer="51"/>
<wire x1="15.137" y1="-1.525" x2="-1.038" y2="-1.525" width="0.05" layer="51"/>
<wire x1="-1.038" y1="-1.525" x2="-1.038" y2="1.525" width="0.05" layer="51"/>
<wire x1="4.725" y1="1.175" x2="9.375" y2="1.175" width="0.1" layer="51"/>
<wire x1="9.375" y1="1.175" x2="9.375" y2="-1.175" width="0.1" layer="51"/>
<wire x1="9.375" y1="-1.175" x2="4.725" y2="-1.175" width="0.1" layer="51"/>
<wire x1="4.725" y1="-1.175" x2="4.725" y2="1.175" width="0.1" layer="51"/>
<wire x1="4.725" y1="0" x2="5.9" y2="1.175" width="0.1" layer="51"/>
<wire x1="0" y1="0" x2="4.725" y2="0" width="0.1" layer="51"/>
<wire x1="9.375" y1="0" x2="14.1" y2="0" width="0.1" layer="51"/>
<wire x1="4.725" y1="1.175" x2="9.375" y2="1.175" width="0.2" layer="21"/>
<wire x1="9.375" y1="1.175" x2="9.375" y2="-1.175" width="0.2" layer="21"/>
<wire x1="9.375" y1="-1.175" x2="4.725" y2="-1.175" width="0.2" layer="21"/>
<wire x1="4.725" y1="-1.175" x2="4.725" y2="1.175" width="0.2" layer="21"/>
<wire x1="4.725" y1="0" x2="5.9" y2="1.175" width="0.2" layer="21"/>
<wire x1="1.138" y1="0" x2="4.725" y2="0" width="0.2" layer="21"/>
<wire x1="9.375" y1="0" x2="12.962" y2="0" width="0.2" layer="21"/>
</package>
<package name="RESAD1526W69L610D229">
<description>&lt;b&gt;CMF552&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="0.9" diameter="1.35"/>
<pad name="2" x="15.3" y="0" drill="0.9" diameter="1.35"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-0.925" y1="1.495" x2="16.225" y2="1.495" width="0.05" layer="51"/>
<wire x1="16.225" y1="1.495" x2="16.225" y2="-1.495" width="0.05" layer="51"/>
<wire x1="16.225" y1="-1.495" x2="-0.925" y2="-1.495" width="0.05" layer="51"/>
<wire x1="-0.925" y1="-1.495" x2="-0.925" y2="1.495" width="0.05" layer="51"/>
<wire x1="4.6" y1="1.145" x2="10.7" y2="1.145" width="0.1" layer="51"/>
<wire x1="10.7" y1="1.145" x2="10.7" y2="-1.145" width="0.1" layer="51"/>
<wire x1="10.7" y1="-1.145" x2="4.6" y2="-1.145" width="0.1" layer="51"/>
<wire x1="4.6" y1="-1.145" x2="4.6" y2="1.145" width="0.1" layer="51"/>
<wire x1="0" y1="0" x2="4.6" y2="0" width="0.1" layer="51"/>
<wire x1="10.7" y1="0" x2="15.3" y2="0" width="0.1" layer="51"/>
<wire x1="4.6" y1="1.145" x2="10.7" y2="1.145" width="0.2" layer="21"/>
<wire x1="10.7" y1="1.145" x2="10.7" y2="-1.145" width="0.2" layer="21"/>
<wire x1="10.7" y1="-1.145" x2="4.6" y2="-1.145" width="0.2" layer="21"/>
<wire x1="4.6" y1="-1.145" x2="4.6" y2="1.145" width="0.2" layer="21"/>
<wire x1="1.025" y1="0" x2="4.6" y2="0" width="0.2" layer="21"/>
<wire x1="10.7" y1="0" x2="14.275" y2="0" width="0.2" layer="21"/>
</package>
<package name="395011002">
<description>&lt;b&gt;39501-1002-4&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1.3" diameter="1.95"/>
<pad name="2" x="3.5" y="0" drill="1.3" diameter="1.95"/>
<text x="1.75" y="0.55" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="1.75" y="0.55" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-2.45" y1="4" x2="5.95" y2="4" width="0.2" layer="51"/>
<wire x1="5.95" y1="4" x2="5.95" y2="-2.9" width="0.2" layer="51"/>
<wire x1="5.95" y1="-2.9" x2="-2.45" y2="-2.9" width="0.2" layer="51"/>
<wire x1="-2.45" y1="-2.9" x2="-2.45" y2="4" width="0.2" layer="51"/>
<wire x1="-2.45" y1="4" x2="5.95" y2="4" width="0.1" layer="21"/>
<wire x1="5.95" y1="4" x2="5.95" y2="-2.9" width="0.1" layer="21"/>
<wire x1="5.95" y1="-2.9" x2="-2.45" y2="-2.9" width="0.1" layer="21"/>
<wire x1="-2.45" y1="-2.9" x2="-2.45" y2="4" width="0.1" layer="21"/>
<wire x1="-3.45" y1="5" x2="6.95" y2="5" width="0.1" layer="51"/>
<wire x1="6.95" y1="5" x2="6.95" y2="-3.9" width="0.1" layer="51"/>
<wire x1="6.95" y1="-3.9" x2="-3.45" y2="-3.9" width="0.1" layer="51"/>
<wire x1="-3.45" y1="-3.9" x2="-3.45" y2="5" width="0.1" layer="51"/>
</package>
<package name="395011008">
<description>&lt;b&gt;39501-1008-2&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1.3" diameter="1.95"/>
<pad name="2" x="3.5" y="0" drill="1.3" diameter="1.95"/>
<pad name="3" x="7" y="0" drill="1.3" diameter="1.95"/>
<pad name="4" x="10.5" y="0" drill="1.3" diameter="1.95"/>
<pad name="5" x="14" y="0" drill="1.3" diameter="1.95"/>
<pad name="6" x="17.5" y="0" drill="1.3" diameter="1.95"/>
<pad name="7" x="21" y="0" drill="1.3" diameter="1.95"/>
<pad name="8" x="24.5" y="0" drill="1.3" diameter="1.95"/>
<text x="12.25" y="0.55" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="12.25" y="0.55" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-2.45" y1="4" x2="26.95" y2="4" width="0.2" layer="51"/>
<wire x1="26.95" y1="4" x2="26.95" y2="-2.9" width="0.2" layer="51"/>
<wire x1="26.95" y1="-2.9" x2="-2.45" y2="-2.9" width="0.2" layer="51"/>
<wire x1="-2.45" y1="-2.9" x2="-2.45" y2="4" width="0.2" layer="51"/>
<wire x1="-2.45" y1="4" x2="26.95" y2="4" width="0.1" layer="21"/>
<wire x1="26.95" y1="4" x2="26.95" y2="-2.9" width="0.1" layer="21"/>
<wire x1="26.95" y1="-2.9" x2="-2.45" y2="-2.9" width="0.1" layer="21"/>
<wire x1="-2.45" y1="-2.9" x2="-2.45" y2="4" width="0.1" layer="21"/>
<wire x1="-3.45" y1="5" x2="27.95" y2="5" width="0.1" layer="51"/>
<wire x1="27.95" y1="5" x2="27.95" y2="-3.9" width="0.1" layer="51"/>
<wire x1="27.95" y1="-3.9" x2="-3.45" y2="-3.9" width="0.1" layer="51"/>
<wire x1="-3.45" y1="-3.9" x2="-3.45" y2="5" width="0.1" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="DF005M">
<wire x1="5.08" y1="2.54" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-5.08" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="19.05" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="19.05" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="~_1" x="0" y="0" length="middle"/>
<pin name="~_2" x="0" y="-2.54" length="middle"/>
<pin name="-" x="22.86" y="0" length="middle" rot="R180"/>
<pin name="+" x="22.86" y="-2.54" length="middle" rot="R180"/>
</symbol>
<symbol name="MGFS1R5243R3">
<wire x1="5.08" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-10.16" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="21.59" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="21.59" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="-VIN" x="0" y="0" length="middle"/>
<pin name="+VIN" x="0" y="-2.54" length="middle"/>
<pin name="+VOUT" x="0" y="-5.08" length="middle"/>
<pin name="-VOUT" x="0" y="-7.62" length="middle"/>
</symbol>
<symbol name="BC548BTA">
<wire x1="7.62" y1="2.54" x2="7.62" y2="-2.54" width="0.508" layer="94"/>
<wire x1="7.62" y1="1.27" x2="10.16" y2="3.81" width="0.254" layer="94"/>
<wire x1="7.62" y1="-1.27" x2="10.16" y2="-3.81" width="0.254" layer="94"/>
<wire x1="10.16" y1="-3.81" x2="10.16" y2="-5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="3.81" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="7.62" y2="0" width="0.254" layer="94"/>
<circle x="8.89" y="0" radius="4.016" width="0.254" layer="94"/>
<text x="13.97" y="1.27" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="13.97" y="-1.27" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="B" x="0" y="0" visible="pad" length="short"/>
<pin name="E" x="10.16" y="-7.62" visible="pad" length="short" rot="R90"/>
<pin name="C" x="10.16" y="7.62" visible="pad" length="short" rot="R270"/>
<polygon width="0.254" layer="94">
<vertex x="8.382" y="-2.54"/>
<vertex x="8.89" y="-2.032"/>
<vertex x="9.398" y="-3.048"/>
</polygon>
</symbol>
<symbol name="APAN3103">
<wire x1="5.08" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-10.16" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="21.59" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="21.59" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="COIL_1" x="0" y="0" length="middle"/>
<pin name="COIL_2" x="0" y="-2.54" length="middle"/>
<pin name="NO" x="0" y="-5.08" length="middle"/>
<pin name="COM" x="0" y="-7.62" length="middle"/>
</symbol>
<symbol name="1N4004RLG">
<wire x1="5.08" y1="0" x2="10.16" y2="2.54" width="0.254" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="10.16" y2="2.54" width="0.254" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<text x="11.43" y="5.08" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="11.43" y="2.54" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="K" x="0" y="0" visible="pad" length="middle"/>
<pin name="A" x="15.24" y="0" visible="pad" length="middle" rot="R180"/>
</symbol>
<symbol name="RN55D1801FB14">
<wire x1="5.08" y1="1.27" x2="12.7" y2="1.27" width="0.254" layer="94"/>
<wire x1="12.7" y1="-1.27" x2="12.7" y2="1.27" width="0.254" layer="94"/>
<wire x1="12.7" y1="-1.27" x2="5.08" y2="-1.27" width="0.254" layer="94"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-1.27" width="0.254" layer="94"/>
<text x="13.97" y="6.35" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="13.97" y="3.81" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" visible="pad" length="middle"/>
<pin name="2" x="17.78" y="0" visible="pad" length="middle" rot="R180"/>
</symbol>
<symbol name="39501-1002">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" length="middle"/>
<pin name="2" x="0" y="-2.54" length="middle"/>
</symbol>
<symbol name="39501-1008">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="5.08" y2="-20.32" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-20.32" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" length="middle"/>
<pin name="2" x="0" y="-2.54" length="middle"/>
<pin name="3" x="0" y="-5.08" length="middle"/>
<pin name="4" x="0" y="-7.62" length="middle"/>
<pin name="5" x="0" y="-10.16" length="middle"/>
<pin name="6" x="0" y="-12.7" length="middle"/>
<pin name="7" x="0" y="-15.24" length="middle"/>
<pin name="8" x="0" y="-17.78" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DF005M" prefix="BR">
<description>&lt;b&gt;ON SEMICONDUCTOR - DF005M - BRIDGE RECTIFIER, 1.5A, 50V, 4DIP&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.onsemi.com/pub/Collateral/DF10M-D.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="DF005M" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP798W58P510L828H330Q4N">
<connects>
<connect gate="G$1" pin="+" pad="3"/>
<connect gate="G$1" pin="-" pad="4"/>
<connect gate="G$1" pin="~_1" pad="1"/>
<connect gate="G$1" pin="~_2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="ON SEMICONDUCTOR - DF005M - BRIDGE RECTIFIER, 1.5A, 50V, 4DIP" constant="no"/>
<attribute name="HEIGHT" value="3.3mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="ON Semiconductor" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="DF005M" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="512-DF005M" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=512-DF005M" constant="no"/>
<attribute name="RS_PART_NUMBER" value="9033686" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="http://uk.rs-online.com/web/p/products/9033686" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MGFS1R5243R3" prefix="PS">
<description>&lt;b&gt;Cosel MGF 1.32W Isolated DC-DC Converter PCB Mount, Voltage in 9  36 V dc, Voltage out 3.3V dc&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://en.cosel.co.jp/tool/tag/pdf/SFE_MGFS.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="MGFS1R5243R3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MGFS1R52415">
<connects>
<connect gate="G$1" pin="+VIN" pad="2"/>
<connect gate="G$1" pin="+VOUT" pad="3"/>
<connect gate="G$1" pin="-VIN" pad="1"/>
<connect gate="G$1" pin="-VOUT" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Cosel MGF 1.32W Isolated DC-DC Converter PCB Mount, Voltage in 9  36 V dc, Voltage out 3.3V dc" constant="no"/>
<attribute name="HEIGHT" value="12mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Cosel" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="MGFS1R5243R3" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="436-MGFS1R5243R3" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=436-MGFS1R5243R3" constant="no"/>
<attribute name="RS_PART_NUMBER" value="1715286P" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="http://uk.rs-online.com/web/p/products/1715286P" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BC548BTA" prefix="Q">
<description>&lt;b&gt;NPN Epitaxial Silicon Transistor, TO-92&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://componentsearchengine.com/Datasheets/2/BC548BTA.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="BC548BTA" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BC548BTA">
<connects>
<connect gate="G$1" pin="B" pad="2"/>
<connect gate="G$1" pin="C" pad="1"/>
<connect gate="G$1" pin="E" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="NPN Epitaxial Silicon Transistor, TO-92" constant="no"/>
<attribute name="HEIGHT" value="5.33mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="ON Semiconductor" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="BC548BTA" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="512-BC548BTA" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=512-BC548BTA" constant="no"/>
<attribute name="RS_PART_NUMBER" value="8031093P" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="http://uk.rs-online.com/web/p/products/8031093P" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="APAN3103" prefix="K">
<description>&lt;b&gt;General Purpose Relays 3.0volts 1 Form A PLC Relay&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://b2b-api.panasonic.eu/file_stream/pids/fileversion/7801"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="APAN3103" x="0" y="0"/>
</gates>
<devices>
<device name="" package="APAN3103">
<connects>
<connect gate="G$1" pin="COIL_1" pad="1"/>
<connect gate="G$1" pin="COIL_2" pad="2"/>
<connect gate="G$1" pin="COM" pad="6"/>
<connect gate="G$1" pin="NO" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="ALLIED_NUMBER" value="70879222" constant="no"/>
<attribute name="ALLIED_PRICE-STOCK" value="https://www.alliedelec.com/panasonic-apan3103/70879222/" constant="no"/>
<attribute name="DESCRIPTION" value="General Purpose Relays 3.0volts 1 Form A PLC Relay" constant="no"/>
<attribute name="HEIGHT" value="12.5mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Panasonic" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="APAN3103" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="769-APAN3103" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=769-APAN3103" constant="no"/>
<attribute name="RS_PART_NUMBER" value="" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="1N4004RLG" prefix="D">
<description>&lt;b&gt;Rectifiers 400V 1A Standard&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.onsemi.com/pub/Collateral/1N4001-D.PDF"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="1N4004RLG" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIOAD1405W86L465D235">
<connects>
<connect gate="G$1" pin="A" pad="2"/>
<connect gate="G$1" pin="K" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Rectifiers 400V 1A Standard" constant="no"/>
<attribute name="HEIGHT" value="mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="ON Semiconductor" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="1N4004RLG" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="863-1N4004RLG" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=863-1N4004RLG" constant="no"/>
<attribute name="RS_PART_NUMBER" value="1844627P" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="http://uk.rs-online.com/web/p/products/1844627P" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RN55D1801FB14" prefix="R">
<description>&lt;b&gt;Metal Film Resistors - Through Hole 1/8watt 1.8Kohms 1% 100ppm&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://componentsearchengine.com/Datasheets/1/RN55D1801FB14.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="RN55D1801FB14" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RESAD1526W69L610D229">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Metal Film Resistors - Through Hole 1/8watt 1.8Kohms 1% 100ppm" constant="no"/>
<attribute name="HEIGHT" value="mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Vishay" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="RN55D1801FB14" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="71-RN55D1801FB14" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=71-RN55D1801FB14" constant="no"/>
<attribute name="RS_PART_NUMBER" value="" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="39501-1002" prefix="J">
<description>&lt;b&gt;Pluggable Terminal Blocks 3.5MM EURO HDR 02P VT CLOSED&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://mouser.componentsearchengine.com/Datasheets/2/39501-1002.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="39501-1002" x="0" y="0"/>
</gates>
<devices>
<device name="" package="395011002">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="ALLIED_NUMBER" value="71469767" constant="no"/>
<attribute name="ALLIED_PRICE-STOCK" value="https://www.alliedelec.com/molexincorporated-39501-1002/71469767/" constant="no"/>
<attribute name="DESCRIPTION" value="Pluggable Terminal Blocks 3.5MM EURO HDR 02P VT CLOSED" constant="no"/>
<attribute name="HEIGHT" value="9.6mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Molex" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="39501-1002" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="538-39501-1002" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=538-39501-1002" constant="no"/>
<attribute name="RS_PART_NUMBER" value="" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="39501-1008" prefix="J">
<description>&lt;b&gt;Pluggable Terminal Blocks EURO 3.5MM 8 CIRCUIT VERT PCB HEADER&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://componentsearchengine.com/Datasheets/1/39501-1008.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="39501-1008" x="0" y="0"/>
</gates>
<devices>
<device name="" package="395011008">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="ALLIED_NUMBER" value="71457797" constant="no"/>
<attribute name="ALLIED_PRICE-STOCK" value="https://www.alliedelec.com/molexincorporated-39501-1008/71457797/" constant="no"/>
<attribute name="DESCRIPTION" value="Pluggable Terminal Blocks EURO 3.5MM 8 CIRCUIT VERT PCB HEADER" constant="no"/>
<attribute name="HEIGHT" value="9.2mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Molex" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="39501-1008" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="538-39501-1008" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=538-39501-1008" constant="no"/>
<attribute name="RS_PART_NUMBER" value="" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="xbee">
<description>&lt;b&gt;MaxSream&lt;/b&gt; XBee Products&lt;p&gt;
http://www.digi.com</description>
<packages>
<package name="XBEE">
<description>&lt;b&gt;XBEE&lt;/b&gt;&lt;p&gt;
Source: http://www.maxstream.net/products/xbee/datasheet_XBee_OEM_RF-Modules.pdf</description>
<wire x1="-12.1" y1="-11.975" x2="-12.1" y2="9.1" width="0.2032" layer="21"/>
<wire x1="-12.1" y1="9.1" x2="-5.775" y2="15.425" width="0.2032" layer="21"/>
<wire x1="-5.775" y1="15.425" x2="5.775" y2="15.425" width="0.2032" layer="21"/>
<wire x1="5.775" y1="15.425" x2="12.1" y2="9.1" width="0.2032" layer="21"/>
<wire x1="12.1" y1="9.1" x2="12.1" y2="-11.975" width="0.2032" layer="21"/>
<wire x1="12.1" y1="-11.975" x2="-12.1" y2="-11.975" width="0.2032" layer="21"/>
<wire x1="-8.3829" y1="2.8685" x2="7.4359" y2="2.8685" width="0.1524" layer="21"/>
<wire x1="-8.3829" y1="-2.4369" x2="7.4359" y2="-2.4369" width="0.1524" layer="21"/>
<wire x1="-7.4082" y1="2.1723" x2="-5.8764" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="2.1723" x2="-5.8764" y2="2.0887" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="2.0887" x2="-5.9182" y2="2.0052" width="0.1016" layer="21"/>
<wire x1="-5.9182" y1="2.0052" x2="-5.8764" y2="1.9355" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="1.9355" x2="-5.8764" y2="1.8659" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="1.8659" x2="-5.5283" y2="0.9886" width="0.1016" layer="21"/>
<wire x1="-5.5283" y1="0.9886" x2="-4.5396" y2="1.9634" width="0.1016" layer="21"/>
<wire x1="-4.5396" y1="1.9634" x2="-4.4839" y2="2.033" width="0.1016" layer="21"/>
<wire x1="-4.4839" y1="2.033" x2="-4.4422" y2="2.1166" width="0.1016" layer="21"/>
<wire x1="-4.4422" y1="2.1166" x2="-4.4282" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-4.4282" y1="2.1723" x2="-3.551" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-3.551" y1="2.1723" x2="-3.732" y2="2.0469" width="0.1016" layer="21"/>
<wire x1="-3.732" y1="2.0469" x2="-3.8712" y2="1.9495" width="0.1016" layer="21"/>
<wire x1="-3.8712" y1="1.9495" x2="-4.0662" y2="1.7824" width="0.1016" layer="21"/>
<wire x1="-4.0662" y1="1.7824" x2="-5.3751" y2="0.557" width="0.1016" layer="21"/>
<wire x1="-5.3751" y1="0.557" x2="-4.5953" y2="-1.3647" width="0.1016" layer="21"/>
<wire x1="-4.5953" y1="-1.3647" x2="-4.3725" y2="-1.671" width="0.1016" layer="21"/>
<wire x1="-4.3725" y1="-1.671" x2="-4.3308" y2="-1.671" width="0.1016" layer="21"/>
<wire x1="-4.3308" y1="-1.671" x2="-4.2472" y2="-1.5875" width="0.1016" layer="21"/>
<wire x1="-4.2472" y1="-1.5875" x2="-4.1358" y2="-1.2533" width="0.1016" layer="21"/>
<wire x1="-4.1358" y1="-1.2533" x2="-3.9687" y2="-0.6267" width="0.1016" layer="21"/>
<wire x1="-3.9687" y1="-0.6267" x2="-3.7738" y2="0.1671" width="0.1016" layer="21"/>
<wire x1="-3.7738" y1="0.1671" x2="-3.4117" y2="1.6431" width="0.1016" layer="21"/>
<wire x1="-3.4117" y1="1.6431" x2="-3.356" y2="1.8938" width="0.1016" layer="21"/>
<wire x1="-3.356" y1="1.8938" x2="-3.356" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-3.356" y1="2.1723" x2="-0.195" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-0.195" y1="2.1723" x2="-0.0279" y2="2.1305" width="0.1016" layer="21"/>
<wire x1="-0.0279" y1="2.1305" x2="0.0835" y2="2.0609" width="0.1016" layer="21"/>
<wire x1="0.0835" y1="2.0609" x2="0.167" y2="1.9077" width="0.1016" layer="21"/>
<wire x1="0.167" y1="1.9077" x2="0.2227" y2="1.7684" width="0.1016" layer="21"/>
<wire x1="0.2227" y1="1.7684" x2="0.2227" y2="1.5317" width="0.1016" layer="21"/>
<wire x1="0.2227" y1="1.5317" x2="0.1809" y2="1.4203" width="0.1016" layer="21"/>
<wire x1="0.1809" y1="1.4203" x2="0.0138" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="0.0138" y1="0.7241" x2="-0.0419" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="-0.0419" y1="0.5848" x2="-0.2507" y2="0.3759" width="0.1016" layer="21"/>
<wire x1="-0.2507" y1="0.3759" x2="-0.4178" y2="0.3063" width="0.1016" layer="21"/>
<wire x1="-0.4178" y1="0.3063" x2="-0.6406" y2="0.2506" width="0.1016" layer="21"/>
<wire x1="-0.6406" y1="0.2506" x2="-0.9191" y2="0.2506" width="0.1016" layer="21"/>
<wire x1="-0.9191" y1="0.2506" x2="-0.5153" y2="0.1949" width="0.1016" layer="21"/>
<wire x1="-0.5153" y1="0.1949" x2="-0.2229" y2="0.0557" width="0.1016" layer="21"/>
<wire x1="-0.2229" y1="0.0557" x2="-0.209" y2="0.0278" width="0.1016" layer="21"/>
<wire x1="-0.209" y1="0.0278" x2="-0.209" y2="-0.3482" width="0.1016" layer="21"/>
<wire x1="-0.209" y1="-0.3482" x2="-0.3621" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="-0.3621" y1="-0.9609" x2="-0.4596" y2="-1.114" width="0.1016" layer="21"/>
<wire x1="-0.4596" y1="-1.114" x2="-0.4875" y2="-1.2811" width="0.1016" layer="21"/>
<wire x1="-0.4875" y1="-1.2811" x2="-0.6963" y2="-1.5179" width="0.1016" layer="21"/>
<wire x1="-0.6963" y1="-1.5179" x2="-0.8634" y2="-1.6014" width="0.1016" layer="21"/>
<wire x1="-0.8634" y1="-1.6014" x2="-1.128" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-1.128" y1="-1.685" x2="-5.96" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-5.96" y1="-1.685" x2="-5.8764" y2="-1.5318" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="-1.5318" x2="-5.8764" y2="-1.4343" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="-1.4343" x2="-6.322" y2="-0.3342" width="0.1016" layer="21"/>
<wire x1="-6.322" y1="-0.3342" x2="-7.4778" y2="-1.4622" width="0.1016" layer="21"/>
<wire x1="-7.4778" y1="-1.4622" x2="-7.6031" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-7.6031" y1="-1.685" x2="-8.4247" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-8.4247" y1="-1.685" x2="-8.0766" y2="-1.4343" width="0.1016" layer="21"/>
<wire x1="-8.0766" y1="-1.4343" x2="-6.4613" y2="0.0835" width="0.1016" layer="21"/>
<wire x1="-6.4613" y1="0.0835" x2="-7.255" y2="2.0191" width="0.1016" layer="21"/>
<wire x1="-7.255" y1="2.0191" x2="-7.4082" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-2.2977" y1="1.6988" x2="-1.0166" y2="1.6988" width="0.1016" layer="21"/>
<wire x1="-1.0166" y1="1.6988" x2="-0.8913" y2="1.6292" width="0.1016" layer="21"/>
<wire x1="-0.8913" y1="1.6292" x2="-0.8774" y2="1.4064" width="0.1016" layer="21"/>
<wire x1="-0.8774" y1="1.4064" x2="-1.0723" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="-1.0723" y1="0.6684" x2="-1.1141" y2="0.5709" width="0.1016" layer="21"/>
<wire x1="-1.1141" y1="0.5709" x2="-1.1976" y2="0.5152" width="0.1016" layer="21"/>
<wire x1="-1.1976" y1="0.5152" x2="-2.5901" y2="0.5152" width="0.1016" layer="21"/>
<wire x1="-2.5901" y1="0.5152" x2="-2.2977" y2="1.6988" width="0.1016" layer="21"/>
<wire x1="-2.6876" y1="0.0139" x2="-1.4204" y2="0.0139" width="0.1016" layer="21"/>
<wire x1="-1.4204" y1="0.0139" x2="-1.309" y2="-0.0279" width="0.1016" layer="21"/>
<wire x1="-1.309" y1="-0.0279" x2="-1.2394" y2="-0.1254" width="0.1016" layer="21"/>
<wire x1="-1.2394" y1="-0.1254" x2="-1.2394" y2="-0.1671" width="0.1016" layer="21"/>
<wire x1="-1.2394" y1="-0.1671" x2="-1.4483" y2="-0.9887" width="0.1016" layer="21"/>
<wire x1="-1.4483" y1="-0.9887" x2="-1.504" y2="-1.0723" width="0.1016" layer="21"/>
<wire x1="-1.504" y1="-1.0723" x2="-1.6015" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="-1.6015" y1="-1.1837" x2="-1.6572" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="-1.6572" y1="-1.2115" x2="-3.0079" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="-3.0079" y1="-1.2115" x2="-2.6876" y2="0.0139" width="0.1016" layer="21"/>
<wire x1="1.3646" y1="-0.0975" x2="1.462" y2="0.4734" width="0.1016" layer="21"/>
<wire x1="1.462" y1="0.4734" x2="1.5038" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="1.5038" y1="0.5848" x2="1.5595" y2="0.6823" width="0.1016" layer="21"/>
<wire x1="1.5595" y1="0.6823" x2="1.6431" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="1.6431" y1="0.7241" x2="2.6317" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="2.6317" y1="0.7241" x2="2.6874" y2="0.7101" width="0.1016" layer="21"/>
<wire x1="2.6874" y1="0.7101" x2="2.7292" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="2.7292" y1="0.6684" x2="2.7292" y2="0.4873" width="0.1016" layer="21"/>
<wire x1="2.7292" y1="0.4873" x2="2.576" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="2.576" y1="-0.1114" x2="1.3785" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="1.3785" y1="-0.1114" x2="1.3646" y2="-0.0975" width="0.1016" layer="21"/>
<wire x1="3.1609" y1="-1.685" x2="0.4037" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="0.4037" y1="-1.685" x2="0.2923" y2="-1.6571" width="0.1016" layer="21"/>
<wire x1="0.2923" y1="-1.6571" x2="0.1809" y2="-1.5736" width="0.1016" layer="21"/>
<wire x1="0.1809" y1="-1.5736" x2="0.1113" y2="-1.4761" width="0.1016" layer="21"/>
<wire x1="0.1113" y1="-1.4761" x2="0.0695" y2="-1.3229" width="0.1016" layer="21"/>
<wire x1="0.0695" y1="-1.3229" x2="0.0695" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="0.0695" y1="-1.1837" x2="0.0974" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="0.0974" y1="-0.9609" x2="0.3759" y2="0.2785" width="0.1016" layer="21"/>
<wire x1="0.3759" y1="0.2785" x2="0.4177" y2="0.4316" width="0.1016" layer="21"/>
<wire x1="0.4177" y1="0.4316" x2="0.5848" y2="0.7658" width="0.1016" layer="21"/>
<wire x1="0.5848" y1="0.7658" x2="0.7101" y2="0.9469" width="0.1016" layer="21"/>
<wire x1="0.7101" y1="0.9469" x2="0.9329" y2="1.0861" width="0.1016" layer="21"/>
<wire x1="0.9329" y1="1.0861" x2="1.1" y2="1.1418" width="0.1016" layer="21"/>
<wire x1="1.1" y1="1.1418" x2="1.1835" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="1.1835" y1="1.1557" x2="3.3698" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="3.3698" y1="1.1557" x2="3.5229" y2="1.1" width="0.1016" layer="21"/>
<wire x1="3.5229" y1="1.1" x2="3.704" y2="0.9608" width="0.1016" layer="21"/>
<wire x1="3.704" y1="0.9608" x2="3.7597" y2="0.9051" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="0.9051" x2="3.7597" y2="0.4177" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="0.4177" x2="3.5229" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="3.5229" y1="-0.5431" x2="1.2392" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="1.2392" y1="-0.5431" x2="1.1278" y2="-1.0166" width="0.1016" layer="21"/>
<wire x1="1.1278" y1="-1.0166" x2="1.1" y2="-1.1001" width="0.1016" layer="21"/>
<wire x1="1.1" y1="-1.1001" x2="1.1139" y2="-1.1976" width="0.1016" layer="21"/>
<wire x1="1.1139" y1="-1.1976" x2="1.1696" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="1.1696" y1="-1.2394" x2="3.1748" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="3.1748" y1="-1.2394" x2="3.3558" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="3.3558" y1="-1.2115" x2="3.1609" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="5.0686" y1="-0.0975" x2="5.166" y2="0.4734" width="0.1016" layer="21"/>
<wire x1="5.166" y1="0.4734" x2="5.2078" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="5.2078" y1="0.5848" x2="5.2635" y2="0.6823" width="0.1016" layer="21"/>
<wire x1="5.2635" y1="0.6823" x2="5.3471" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="5.3471" y1="0.7241" x2="6.3357" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="6.3357" y1="0.7241" x2="6.3914" y2="0.7101" width="0.1016" layer="21"/>
<wire x1="6.3914" y1="0.7101" x2="6.4332" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="6.4332" y1="0.6684" x2="6.4332" y2="0.4873" width="0.1016" layer="21"/>
<wire x1="6.4332" y1="0.4873" x2="6.28" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="6.28" y1="-0.1114" x2="5.0825" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="5.0825" y1="-0.1114" x2="5.0686" y2="-0.0975" width="0.1016" layer="21"/>
<wire x1="6.8649" y1="-1.685" x2="4.1077" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="4.1077" y1="-1.685" x2="3.9963" y2="-1.6571" width="0.1016" layer="21"/>
<wire x1="3.9963" y1="-1.6571" x2="3.8849" y2="-1.5736" width="0.1016" layer="21"/>
<wire x1="3.8849" y1="-1.5736" x2="3.8153" y2="-1.4761" width="0.1016" layer="21"/>
<wire x1="3.8153" y1="-1.4761" x2="3.7735" y2="-1.3229" width="0.1016" layer="21"/>
<wire x1="3.7735" y1="-1.3229" x2="3.7735" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="3.7735" y1="-1.1837" x2="3.8014" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="3.8014" y1="-0.9609" x2="4.0799" y2="0.2785" width="0.1016" layer="21"/>
<wire x1="4.0799" y1="0.2785" x2="4.1217" y2="0.4316" width="0.1016" layer="21"/>
<wire x1="4.1217" y1="0.4316" x2="4.2888" y2="0.7658" width="0.1016" layer="21"/>
<wire x1="4.2888" y1="0.7658" x2="4.4141" y2="0.9469" width="0.1016" layer="21"/>
<wire x1="4.4141" y1="0.9469" x2="4.6369" y2="1.0861" width="0.1016" layer="21"/>
<wire x1="4.6369" y1="1.0861" x2="4.804" y2="1.1418" width="0.1016" layer="21"/>
<wire x1="4.804" y1="1.1418" x2="4.8875" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="4.8875" y1="1.1557" x2="7.0738" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="7.0738" y1="1.1557" x2="7.2269" y2="1.1" width="0.1016" layer="21"/>
<wire x1="7.2269" y1="1.1" x2="7.408" y2="0.9608" width="0.1016" layer="21"/>
<wire x1="7.408" y1="0.9608" x2="7.4637" y2="0.9051" width="0.1016" layer="21"/>
<wire x1="7.4637" y1="0.9051" x2="7.4637" y2="0.4177" width="0.1016" layer="21"/>
<wire x1="7.4637" y1="0.4177" x2="7.2269" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="7.2269" y1="-0.5431" x2="4.9432" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="4.9432" y1="-0.5431" x2="4.8318" y2="-1.0166" width="0.1016" layer="21"/>
<wire x1="4.8318" y1="-1.0166" x2="4.804" y2="-1.1001" width="0.1016" layer="21"/>
<wire x1="4.804" y1="-1.1001" x2="4.8179" y2="-1.1976" width="0.1016" layer="21"/>
<wire x1="4.8179" y1="-1.1976" x2="4.8736" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="4.8736" y1="-1.2394" x2="6.8788" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="6.8788" y1="-1.2394" x2="7.0598" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="7.0598" y1="-1.2115" x2="6.8649" y2="-1.685" width="0.1016" layer="21"/>
<pad name="1" x="-11" y="9" drill="0.8" diameter="1.27"/>
<pad name="2" x="-11" y="7" drill="0.8" diameter="1.27"/>
<pad name="3" x="-11" y="5" drill="0.8" diameter="1.27"/>
<pad name="4" x="-11" y="3" drill="0.8" diameter="1.27"/>
<pad name="5" x="-11" y="1" drill="0.8" diameter="1.27"/>
<pad name="6" x="-11" y="-1" drill="0.8" diameter="1.27"/>
<pad name="7" x="-11" y="-3" drill="0.8" diameter="1.27"/>
<pad name="8" x="-11" y="-5" drill="0.8" diameter="1.27"/>
<pad name="9" x="-11" y="-7" drill="0.8" diameter="1.27"/>
<pad name="10" x="-11" y="-9" drill="0.8" diameter="1.27"/>
<pad name="11" x="11" y="-9" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="12" x="11" y="-7" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="13" x="11" y="-5" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="14" x="11" y="-3" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="15" x="11" y="-1" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="16" x="11" y="1" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="17" x="11" y="3" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="18" x="11" y="5" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="19" x="11" y="7" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="20" x="11" y="9" drill="0.8" diameter="1.27" rot="R180"/>
<text x="-11.43" y="13.97" size="1.27" layer="25">&gt;NAME</text>
<text x="-11.43" y="-13.97" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="XBEE-PRO">
<description>&lt;b&gt;XBEE Pro&lt;/b&gt;&lt;p&gt;</description>
<wire x1="-12.1" y1="-17.305" x2="-12.1" y2="9.1" width="0.2032" layer="21"/>
<wire x1="-12.1" y1="9.1" x2="-5.775" y2="15.425" width="0.2032" layer="21"/>
<wire x1="-5.775" y1="15.425" x2="5.775" y2="15.425" width="0.2032" layer="21"/>
<wire x1="5.775" y1="15.425" x2="12.1" y2="9.1" width="0.2032" layer="21"/>
<wire x1="12.1" y1="9.1" x2="12.1" y2="-17.305" width="0.2032" layer="21"/>
<wire x1="12.1" y1="-17.305" x2="-12.1" y2="-17.305" width="0.2032" layer="21"/>
<wire x1="-8.3829" y1="2.8685" x2="7.4359" y2="2.8685" width="0.1524" layer="21"/>
<wire x1="-8.3829" y1="-2.4369" x2="7.4359" y2="-2.4369" width="0.1524" layer="21"/>
<wire x1="-7.4082" y1="2.1723" x2="-5.8764" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="2.1723" x2="-5.8764" y2="2.0887" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="2.0887" x2="-5.9182" y2="2.0052" width="0.1016" layer="21"/>
<wire x1="-5.9182" y1="2.0052" x2="-5.8764" y2="1.9355" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="1.9355" x2="-5.8764" y2="1.8659" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="1.8659" x2="-5.5283" y2="0.9886" width="0.1016" layer="21"/>
<wire x1="-5.5283" y1="0.9886" x2="-4.5396" y2="1.9634" width="0.1016" layer="21"/>
<wire x1="-4.5396" y1="1.9634" x2="-4.4839" y2="2.033" width="0.1016" layer="21"/>
<wire x1="-4.4839" y1="2.033" x2="-4.4422" y2="2.1166" width="0.1016" layer="21"/>
<wire x1="-4.4422" y1="2.1166" x2="-4.4282" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-4.4282" y1="2.1723" x2="-3.551" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-3.551" y1="2.1723" x2="-3.732" y2="2.0469" width="0.1016" layer="21"/>
<wire x1="-3.732" y1="2.0469" x2="-3.8712" y2="1.9495" width="0.1016" layer="21"/>
<wire x1="-3.8712" y1="1.9495" x2="-4.0662" y2="1.7824" width="0.1016" layer="21"/>
<wire x1="-4.0662" y1="1.7824" x2="-5.3751" y2="0.557" width="0.1016" layer="21"/>
<wire x1="-5.3751" y1="0.557" x2="-4.5953" y2="-1.3647" width="0.1016" layer="21"/>
<wire x1="-4.5953" y1="-1.3647" x2="-4.3725" y2="-1.671" width="0.1016" layer="21"/>
<wire x1="-4.3725" y1="-1.671" x2="-4.3308" y2="-1.671" width="0.1016" layer="21"/>
<wire x1="-4.3308" y1="-1.671" x2="-4.2472" y2="-1.5875" width="0.1016" layer="21"/>
<wire x1="-4.2472" y1="-1.5875" x2="-4.1358" y2="-1.2533" width="0.1016" layer="21"/>
<wire x1="-4.1358" y1="-1.2533" x2="-3.9687" y2="-0.6267" width="0.1016" layer="21"/>
<wire x1="-3.9687" y1="-0.6267" x2="-3.7738" y2="0.1671" width="0.1016" layer="21"/>
<wire x1="-3.7738" y1="0.1671" x2="-3.4117" y2="1.6431" width="0.1016" layer="21"/>
<wire x1="-3.4117" y1="1.6431" x2="-3.356" y2="1.8938" width="0.1016" layer="21"/>
<wire x1="-3.356" y1="1.8938" x2="-3.356" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-3.356" y1="2.1723" x2="-0.195" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-0.195" y1="2.1723" x2="-0.0279" y2="2.1305" width="0.1016" layer="21"/>
<wire x1="-0.0279" y1="2.1305" x2="0.0835" y2="2.0609" width="0.1016" layer="21"/>
<wire x1="0.0835" y1="2.0609" x2="0.167" y2="1.9077" width="0.1016" layer="21"/>
<wire x1="0.167" y1="1.9077" x2="0.2227" y2="1.7684" width="0.1016" layer="21"/>
<wire x1="0.2227" y1="1.7684" x2="0.2227" y2="1.5317" width="0.1016" layer="21"/>
<wire x1="0.2227" y1="1.5317" x2="0.1809" y2="1.4203" width="0.1016" layer="21"/>
<wire x1="0.1809" y1="1.4203" x2="0.0138" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="0.0138" y1="0.7241" x2="-0.0419" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="-0.0419" y1="0.5848" x2="-0.2507" y2="0.3759" width="0.1016" layer="21"/>
<wire x1="-0.2507" y1="0.3759" x2="-0.4178" y2="0.3063" width="0.1016" layer="21"/>
<wire x1="-0.4178" y1="0.3063" x2="-0.6406" y2="0.2506" width="0.1016" layer="21"/>
<wire x1="-0.6406" y1="0.2506" x2="-0.9191" y2="0.2506" width="0.1016" layer="21"/>
<wire x1="-0.9191" y1="0.2506" x2="-0.5153" y2="0.1949" width="0.1016" layer="21"/>
<wire x1="-0.5153" y1="0.1949" x2="-0.2229" y2="0.0557" width="0.1016" layer="21"/>
<wire x1="-0.2229" y1="0.0557" x2="-0.209" y2="0.0278" width="0.1016" layer="21"/>
<wire x1="-0.209" y1="0.0278" x2="-0.209" y2="-0.3482" width="0.1016" layer="21"/>
<wire x1="-0.209" y1="-0.3482" x2="-0.3621" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="-0.3621" y1="-0.9609" x2="-0.4596" y2="-1.114" width="0.1016" layer="21"/>
<wire x1="-0.4596" y1="-1.114" x2="-0.4875" y2="-1.2811" width="0.1016" layer="21"/>
<wire x1="-0.4875" y1="-1.2811" x2="-0.6963" y2="-1.5179" width="0.1016" layer="21"/>
<wire x1="-0.6963" y1="-1.5179" x2="-0.8634" y2="-1.6014" width="0.1016" layer="21"/>
<wire x1="-0.8634" y1="-1.6014" x2="-1.128" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-1.128" y1="-1.685" x2="-5.96" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-5.96" y1="-1.685" x2="-5.8764" y2="-1.5318" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="-1.5318" x2="-5.8764" y2="-1.4343" width="0.1016" layer="21"/>
<wire x1="-5.8764" y1="-1.4343" x2="-6.322" y2="-0.3342" width="0.1016" layer="21"/>
<wire x1="-6.322" y1="-0.3342" x2="-7.4778" y2="-1.4622" width="0.1016" layer="21"/>
<wire x1="-7.4778" y1="-1.4622" x2="-7.6031" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-7.6031" y1="-1.685" x2="-8.4247" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="-8.4247" y1="-1.685" x2="-8.0766" y2="-1.4343" width="0.1016" layer="21"/>
<wire x1="-8.0766" y1="-1.4343" x2="-6.4613" y2="0.0835" width="0.1016" layer="21"/>
<wire x1="-6.4613" y1="0.0835" x2="-7.255" y2="2.0191" width="0.1016" layer="21"/>
<wire x1="-7.255" y1="2.0191" x2="-7.4082" y2="2.1723" width="0.1016" layer="21"/>
<wire x1="-2.2977" y1="1.6988" x2="-1.0166" y2="1.6988" width="0.1016" layer="21"/>
<wire x1="-1.0166" y1="1.6988" x2="-0.8913" y2="1.6292" width="0.1016" layer="21"/>
<wire x1="-0.8913" y1="1.6292" x2="-0.8774" y2="1.4064" width="0.1016" layer="21"/>
<wire x1="-0.8774" y1="1.4064" x2="-1.0723" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="-1.0723" y1="0.6684" x2="-1.1141" y2="0.5709" width="0.1016" layer="21"/>
<wire x1="-1.1141" y1="0.5709" x2="-1.1976" y2="0.5152" width="0.1016" layer="21"/>
<wire x1="-1.1976" y1="0.5152" x2="-2.5901" y2="0.5152" width="0.1016" layer="21"/>
<wire x1="-2.5901" y1="0.5152" x2="-2.2977" y2="1.6988" width="0.1016" layer="21"/>
<wire x1="-2.6876" y1="0.0139" x2="-1.4204" y2="0.0139" width="0.1016" layer="21"/>
<wire x1="-1.4204" y1="0.0139" x2="-1.309" y2="-0.0279" width="0.1016" layer="21"/>
<wire x1="-1.309" y1="-0.0279" x2="-1.2394" y2="-0.1254" width="0.1016" layer="21"/>
<wire x1="-1.2394" y1="-0.1254" x2="-1.2394" y2="-0.1671" width="0.1016" layer="21"/>
<wire x1="-1.2394" y1="-0.1671" x2="-1.4483" y2="-0.9887" width="0.1016" layer="21"/>
<wire x1="-1.4483" y1="-0.9887" x2="-1.504" y2="-1.0723" width="0.1016" layer="21"/>
<wire x1="-1.504" y1="-1.0723" x2="-1.6015" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="-1.6015" y1="-1.1837" x2="-1.6572" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="-1.6572" y1="-1.2115" x2="-3.0079" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="-3.0079" y1="-1.2115" x2="-2.6876" y2="0.0139" width="0.1016" layer="21"/>
<wire x1="1.3646" y1="-0.0975" x2="1.462" y2="0.4734" width="0.1016" layer="21"/>
<wire x1="1.462" y1="0.4734" x2="1.5038" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="1.5038" y1="0.5848" x2="1.5595" y2="0.6823" width="0.1016" layer="21"/>
<wire x1="1.5595" y1="0.6823" x2="1.6431" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="1.6431" y1="0.7241" x2="2.6317" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="2.6317" y1="0.7241" x2="2.6874" y2="0.7101" width="0.1016" layer="21"/>
<wire x1="2.6874" y1="0.7101" x2="2.7292" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="2.7292" y1="0.6684" x2="2.7292" y2="0.4873" width="0.1016" layer="21"/>
<wire x1="2.7292" y1="0.4873" x2="2.576" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="2.576" y1="-0.1114" x2="1.3785" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="1.3785" y1="-0.1114" x2="1.3646" y2="-0.0975" width="0.1016" layer="21"/>
<wire x1="3.1609" y1="-1.685" x2="0.4037" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="0.4037" y1="-1.685" x2="0.2923" y2="-1.6571" width="0.1016" layer="21"/>
<wire x1="0.2923" y1="-1.6571" x2="0.1809" y2="-1.5736" width="0.1016" layer="21"/>
<wire x1="0.1809" y1="-1.5736" x2="0.1113" y2="-1.4761" width="0.1016" layer="21"/>
<wire x1="0.1113" y1="-1.4761" x2="0.0695" y2="-1.3229" width="0.1016" layer="21"/>
<wire x1="0.0695" y1="-1.3229" x2="0.0695" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="0.0695" y1="-1.1837" x2="0.0974" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="0.0974" y1="-0.9609" x2="0.3759" y2="0.2785" width="0.1016" layer="21"/>
<wire x1="0.3759" y1="0.2785" x2="0.4177" y2="0.4316" width="0.1016" layer="21"/>
<wire x1="0.4177" y1="0.4316" x2="0.5848" y2="0.7658" width="0.1016" layer="21"/>
<wire x1="0.5848" y1="0.7658" x2="0.7101" y2="0.9469" width="0.1016" layer="21"/>
<wire x1="0.7101" y1="0.9469" x2="0.9329" y2="1.0861" width="0.1016" layer="21"/>
<wire x1="0.9329" y1="1.0861" x2="1.1" y2="1.1418" width="0.1016" layer="21"/>
<wire x1="1.1" y1="1.1418" x2="1.1835" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="1.1835" y1="1.1557" x2="3.3698" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="3.3698" y1="1.1557" x2="3.5229" y2="1.1" width="0.1016" layer="21"/>
<wire x1="3.5229" y1="1.1" x2="3.704" y2="0.9608" width="0.1016" layer="21"/>
<wire x1="3.704" y1="0.9608" x2="3.7597" y2="0.9051" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="0.9051" x2="3.7597" y2="0.4177" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="0.4177" x2="3.5229" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="3.5229" y1="-0.5431" x2="1.2392" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="1.2392" y1="-0.5431" x2="1.1278" y2="-1.0166" width="0.1016" layer="21"/>
<wire x1="1.1278" y1="-1.0166" x2="1.1" y2="-1.1001" width="0.1016" layer="21"/>
<wire x1="1.1" y1="-1.1001" x2="1.1139" y2="-1.1976" width="0.1016" layer="21"/>
<wire x1="1.1139" y1="-1.1976" x2="1.1696" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="1.1696" y1="-1.2394" x2="3.1748" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="3.1748" y1="-1.2394" x2="3.3558" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="3.3558" y1="-1.2115" x2="3.1609" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="5.0686" y1="-0.0975" x2="5.166" y2="0.4734" width="0.1016" layer="21"/>
<wire x1="5.166" y1="0.4734" x2="5.2078" y2="0.5848" width="0.1016" layer="21"/>
<wire x1="5.2078" y1="0.5848" x2="5.2635" y2="0.6823" width="0.1016" layer="21"/>
<wire x1="5.2635" y1="0.6823" x2="5.3471" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="5.3471" y1="0.7241" x2="6.3357" y2="0.7241" width="0.1016" layer="21"/>
<wire x1="6.3357" y1="0.7241" x2="6.3914" y2="0.7101" width="0.1016" layer="21"/>
<wire x1="6.3914" y1="0.7101" x2="6.4332" y2="0.6684" width="0.1016" layer="21"/>
<wire x1="6.4332" y1="0.6684" x2="6.4332" y2="0.4873" width="0.1016" layer="21"/>
<wire x1="6.4332" y1="0.4873" x2="6.28" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="6.28" y1="-0.1114" x2="5.0825" y2="-0.1114" width="0.1016" layer="21"/>
<wire x1="5.0825" y1="-0.1114" x2="5.0686" y2="-0.0975" width="0.1016" layer="21"/>
<wire x1="6.8649" y1="-1.685" x2="4.1077" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="4.1077" y1="-1.685" x2="3.9963" y2="-1.6571" width="0.1016" layer="21"/>
<wire x1="3.9963" y1="-1.6571" x2="3.8849" y2="-1.5736" width="0.1016" layer="21"/>
<wire x1="3.8849" y1="-1.5736" x2="3.8153" y2="-1.4761" width="0.1016" layer="21"/>
<wire x1="3.8153" y1="-1.4761" x2="3.7735" y2="-1.3229" width="0.1016" layer="21"/>
<wire x1="3.7735" y1="-1.3229" x2="3.7735" y2="-1.1837" width="0.1016" layer="21"/>
<wire x1="3.7735" y1="-1.1837" x2="3.8014" y2="-0.9609" width="0.1016" layer="21"/>
<wire x1="3.8014" y1="-0.9609" x2="4.0799" y2="0.2785" width="0.1016" layer="21"/>
<wire x1="4.0799" y1="0.2785" x2="4.1217" y2="0.4316" width="0.1016" layer="21"/>
<wire x1="4.1217" y1="0.4316" x2="4.2888" y2="0.7658" width="0.1016" layer="21"/>
<wire x1="4.2888" y1="0.7658" x2="4.4141" y2="0.9469" width="0.1016" layer="21"/>
<wire x1="4.4141" y1="0.9469" x2="4.6369" y2="1.0861" width="0.1016" layer="21"/>
<wire x1="4.6369" y1="1.0861" x2="4.804" y2="1.1418" width="0.1016" layer="21"/>
<wire x1="4.804" y1="1.1418" x2="4.8875" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="4.8875" y1="1.1557" x2="7.0738" y2="1.1557" width="0.1016" layer="21"/>
<wire x1="7.0738" y1="1.1557" x2="7.2269" y2="1.1" width="0.1016" layer="21"/>
<wire x1="7.2269" y1="1.1" x2="7.408" y2="0.9608" width="0.1016" layer="21"/>
<wire x1="7.408" y1="0.9608" x2="7.4637" y2="0.9051" width="0.1016" layer="21"/>
<wire x1="7.4637" y1="0.9051" x2="7.4637" y2="0.4177" width="0.1016" layer="21"/>
<wire x1="7.4637" y1="0.4177" x2="7.2269" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="7.2269" y1="-0.5431" x2="4.9432" y2="-0.5431" width="0.1016" layer="21"/>
<wire x1="4.9432" y1="-0.5431" x2="4.8318" y2="-1.0166" width="0.1016" layer="21"/>
<wire x1="4.8318" y1="-1.0166" x2="4.804" y2="-1.1001" width="0.1016" layer="21"/>
<wire x1="4.804" y1="-1.1001" x2="4.8179" y2="-1.1976" width="0.1016" layer="21"/>
<wire x1="4.8179" y1="-1.1976" x2="4.8736" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="4.8736" y1="-1.2394" x2="6.8788" y2="-1.2394" width="0.1016" layer="21"/>
<wire x1="6.8788" y1="-1.2394" x2="7.0598" y2="-1.2115" width="0.1016" layer="21"/>
<wire x1="7.0598" y1="-1.2115" x2="6.8649" y2="-1.685" width="0.1016" layer="21"/>
<wire x1="0.2923" y1="-3.4117" x2="0.4177" y2="-3.4117" width="0.1016" layer="21"/>
<wire x1="0.4177" y1="-3.4117" x2="0.5291" y2="-3.3281" width="0.1016" layer="21"/>
<wire x1="0.5291" y1="-3.3281" x2="0.6405" y2="-3.2167" width="0.1016" layer="21"/>
<wire x1="0.6405" y1="-3.2167" x2="0.7658" y2="-3.2863" width="0.1016" layer="21"/>
<wire x1="0.7658" y1="-3.2863" x2="1.2671" y2="-3.2863" width="0.1016" layer="21"/>
<wire x1="1.2671" y1="-3.2863" x2="1.6709" y2="-3.3281" width="0.1016" layer="21"/>
<wire x1="1.6709" y1="-3.3281" x2="1.9494" y2="-3.4952" width="0.1016" layer="21"/>
<wire x1="1.9494" y1="-3.4952" x2="2.019" y2="-3.6205" width="0.1016" layer="21"/>
<wire x1="2.019" y1="-3.6205" x2="2.019" y2="-3.6762" width="0.1016" layer="21"/>
<wire x1="2.019" y1="-3.6762" x2="1.9633" y2="-3.8016" width="0.1016" layer="21"/>
<wire x1="1.9633" y1="-3.8016" x2="1.8798" y2="-3.899" width="0.1016" layer="21"/>
<wire x1="1.8798" y1="-3.899" x2="1.7127" y2="-4.0104" width="0.1016" layer="21"/>
<wire x1="1.7127" y1="-4.0104" x2="1.1" y2="-4.3168" width="0.1016" layer="21"/>
<wire x1="1.1" y1="-4.3168" x2="0.7797" y2="-4.4421" width="0.1016" layer="21"/>
<wire x1="0.7797" y1="-4.4421" x2="0.5291" y2="-4.4978" width="0.1016" layer="21"/>
<wire x1="0.5291" y1="-4.4978" x2="0.4455" y2="-4.5117" width="0.1016" layer="21"/>
<wire x1="0.4455" y1="-4.5117" x2="0.348" y2="-4.5117" width="0.1016" layer="21"/>
<wire x1="0.348" y1="-4.5117" x2="0.3063" y2="-4.6371" width="0.1016" layer="21"/>
<wire x1="0.3063" y1="-4.6371" x2="0.2227" y2="-4.8877" width="0.1016" layer="21"/>
<wire x1="0.2227" y1="-4.8877" x2="0.1531" y2="-5.1105" width="0.1016" layer="21"/>
<wire x1="0.1531" y1="-5.1105" x2="0.0974" y2="-5.208" width="0.1016" layer="21"/>
<wire x1="0.0974" y1="-5.208" x2="0.0695" y2="-5.2637" width="0.1016" layer="21"/>
<wire x1="0.0695" y1="-5.2637" x2="0.0138" y2="-5.2915" width="0.1016" layer="21"/>
<wire x1="0.0138" y1="-5.2915" x2="-0.0558" y2="-5.2498" width="0.1016" layer="21"/>
<wire x1="-0.0558" y1="-5.2498" x2="-0.1115" y2="-5.1662" width="0.1016" layer="21"/>
<wire x1="-0.1115" y1="-5.1662" x2="-0.1115" y2="-5.0687" width="0.1016" layer="21"/>
<wire x1="-0.1115" y1="-5.0687" x2="-0.0836" y2="-4.9573" width="0.1016" layer="21"/>
<wire x1="-0.0836" y1="-4.9573" x2="0.0417" y2="-4.6928" width="0.1016" layer="21"/>
<wire x1="0.0417" y1="-4.6928" x2="0.1252" y2="-4.4978" width="0.1016" layer="21"/>
<wire x1="0.1252" y1="-4.4978" x2="0.1531" y2="-4.3168" width="0.1016" layer="21"/>
<wire x1="0.1531" y1="-4.3168" x2="0.1949" y2="-4.1497" width="0.1016" layer="21"/>
<wire x1="0.1949" y1="-4.1497" x2="0.2645" y2="-3.9269" width="0.1016" layer="21"/>
<wire x1="0.2645" y1="-3.9269" x2="0.3341" y2="-3.7598" width="0.1016" layer="21"/>
<wire x1="0.3341" y1="-3.7598" x2="0.4037" y2="-3.6484" width="0.1016" layer="21"/>
<wire x1="0.4037" y1="-3.6484" x2="0.2923" y2="-3.6484" width="0.1016" layer="21"/>
<wire x1="0.2923" y1="-3.6484" x2="0.2923" y2="-3.4117" width="0.1016" layer="21"/>
<wire x1="0.7797" y1="-3.5648" x2="1.4899" y2="-3.5648" width="0.1016" layer="21"/>
<wire x1="1.4899" y1="-3.5648" x2="1.657" y2="-3.6345" width="0.1016" layer="21"/>
<wire x1="1.657" y1="-3.6345" x2="1.6988" y2="-3.6623" width="0.1016" layer="21"/>
<wire x1="1.6988" y1="-3.6623" x2="1.6848" y2="-3.7041" width="0.1016" layer="21"/>
<wire x1="1.6848" y1="-3.7041" x2="1.6152" y2="-3.7598" width="0.1016" layer="21"/>
<wire x1="1.6152" y1="-3.7598" x2="1.3924" y2="-3.8712" width="0.1016" layer="21"/>
<wire x1="1.3924" y1="-3.8712" x2="1.2114" y2="-3.9965" width="0.1016" layer="21"/>
<wire x1="1.2114" y1="-3.9965" x2="0.9607" y2="-4.0661" width="0.1016" layer="21"/>
<wire x1="0.9607" y1="-4.0661" x2="0.7797" y2="-4.1358" width="0.1016" layer="21"/>
<wire x1="0.7797" y1="-4.1358" x2="0.6683" y2="-4.1497" width="0.1016" layer="21"/>
<wire x1="0.6683" y1="-4.1497" x2="0.5012" y2="-4.1497" width="0.1016" layer="21"/>
<wire x1="0.5012" y1="-4.1497" x2="0.7519" y2="-3.6345" width="0.1016" layer="21"/>
<wire x1="0.7519" y1="-3.6345" x2="0.7797" y2="-3.5648" width="0.1016" layer="21"/>
<wire x1="2.6596" y1="-3.6345" x2="2.6178" y2="-3.5788" width="0.1016" layer="21"/>
<wire x1="2.6178" y1="-3.5788" x2="2.5482" y2="-3.537" width="0.1016" layer="21"/>
<wire x1="2.5482" y1="-3.537" x2="2.5203" y2="-3.4813" width="0.1016" layer="21"/>
<wire x1="2.5203" y1="-3.4813" x2="2.5343" y2="-3.3977" width="0.1016" layer="21"/>
<wire x1="2.5343" y1="-3.3977" x2="2.6178" y2="-3.3142" width="0.1016" layer="21"/>
<wire x1="2.6178" y1="-3.3142" x2="2.771" y2="-3.2585" width="0.1016" layer="21"/>
<wire x1="2.771" y1="-3.2585" x2="2.952" y2="-3.1889" width="0.1016" layer="21"/>
<wire x1="2.952" y1="-3.1889" x2="3.7597" y2="-3.1889" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="-3.1889" x2="3.9268" y2="-3.2306" width="0.1016" layer="21"/>
<wire x1="3.9268" y1="-3.2306" x2="4.1217" y2="-3.3003" width="0.1016" layer="21"/>
<wire x1="4.1217" y1="-3.3003" x2="4.2331" y2="-3.3699" width="0.1016" layer="21"/>
<wire x1="4.2331" y1="-3.3699" x2="4.3306" y2="-3.4813" width="0.1016" layer="21"/>
<wire x1="4.3306" y1="-3.4813" x2="4.3584" y2="-3.5509" width="0.1016" layer="21"/>
<wire x1="4.3584" y1="-3.5509" x2="4.2888" y2="-3.6762" width="0.1016" layer="21"/>
<wire x1="4.2888" y1="-3.6762" x2="4.2888" y2="-3.7876" width="0.1016" layer="21"/>
<wire x1="4.2888" y1="-3.7876" x2="4.1774" y2="-3.899" width="0.1016" layer="21"/>
<wire x1="4.1774" y1="-3.899" x2="4.0242" y2="-3.9965" width="0.1016" layer="21"/>
<wire x1="4.0242" y1="-3.9965" x2="3.7179" y2="-4.1358" width="0.1016" layer="21"/>
<wire x1="3.7179" y1="-4.1358" x2="3.4255" y2="-4.3168" width="0.1016" layer="21"/>
<wire x1="3.4255" y1="-4.3168" x2="3.2862" y2="-4.4003" width="0.1016" layer="21"/>
<wire x1="3.2862" y1="-4.4003" x2="3.4951" y2="-4.6092" width="0.1016" layer="21"/>
<wire x1="3.4951" y1="-4.6092" x2="3.7597" y2="-4.7902" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="-4.7902" x2="3.9546" y2="-4.9434" width="0.1016" layer="21"/>
<wire x1="3.9546" y1="-4.9434" x2="4.066" y2="-5.0827" width="0.1016" layer="21"/>
<wire x1="4.066" y1="-5.0827" x2="4.1217" y2="-5.2219" width="0.1016" layer="21"/>
<wire x1="4.1217" y1="-5.2219" x2="4.1356" y2="-5.3055" width="0.1016" layer="21"/>
<wire x1="4.1356" y1="-5.3055" x2="4.0939" y2="-5.389" width="0.1016" layer="21"/>
<wire x1="4.0939" y1="-5.389" x2="4.0521" y2="-5.4029" width="0.1016" layer="21"/>
<wire x1="4.0521" y1="-5.4029" x2="3.9407" y2="-5.3194" width="0.1016" layer="21"/>
<wire x1="3.9407" y1="-5.3194" x2="3.3976" y2="-4.8877" width="0.1016" layer="21"/>
<wire x1="3.3976" y1="-4.8877" x2="2.8824" y2="-4.5396" width="0.1016" layer="21"/>
<wire x1="2.8824" y1="-4.5396" x2="2.7849" y2="-4.5396" width="0.1016" layer="21"/>
<wire x1="2.7849" y1="-4.5396" x2="2.7571" y2="-4.6371" width="0.1016" layer="21"/>
<wire x1="2.7571" y1="-4.6371" x2="2.6596" y2="-4.9156" width="0.1016" layer="21"/>
<wire x1="2.6596" y1="-4.9156" x2="2.576" y2="-5.1662" width="0.1016" layer="21"/>
<wire x1="2.576" y1="-5.1662" x2="2.5203" y2="-5.3055" width="0.1016" layer="21"/>
<wire x1="2.5203" y1="-5.3055" x2="2.5203" y2="-5.389" width="0.1016" layer="21"/>
<wire x1="2.5203" y1="-5.389" x2="2.3672" y2="-5.2498" width="0.1016" layer="21"/>
<wire x1="2.3672" y1="-5.2498" x2="2.3532" y2="-5.0409" width="0.1016" layer="21"/>
<wire x1="2.3532" y1="-5.0409" x2="2.3811" y2="-4.9016" width="0.1016" layer="21"/>
<wire x1="2.3811" y1="-4.9016" x2="2.5064" y2="-4.456" width="0.1016" layer="21"/>
<wire x1="2.5064" y1="-4.456" x2="2.576" y2="-4.2054" width="0.1016" layer="21"/>
<wire x1="2.576" y1="-4.2054" x2="2.7292" y2="-3.8573" width="0.1016" layer="21"/>
<wire x1="2.7292" y1="-3.8573" x2="2.8267" y2="-3.6762" width="0.1016" layer="21"/>
<wire x1="2.8267" y1="-3.6762" x2="2.8685" y2="-3.5788" width="0.1016" layer="21"/>
<wire x1="2.8685" y1="-3.5788" x2="2.771" y2="-3.5648" width="0.1016" layer="21"/>
<wire x1="2.771" y1="-3.5648" x2="2.6596" y2="-3.6484" width="0.1016" layer="21"/>
<wire x1="2.6596" y1="-3.6484" x2="2.6596" y2="-3.6345" width="0.1016" layer="21"/>
<wire x1="3.2584" y1="-3.5231" x2="3.7597" y2="-3.5231" width="0.1016" layer="21"/>
<wire x1="3.7597" y1="-3.5231" x2="3.9268" y2="-3.5509" width="0.1016" layer="21"/>
<wire x1="3.9268" y1="-3.5509" x2="3.9685" y2="-3.6345" width="0.1016" layer="21"/>
<wire x1="3.9685" y1="-3.6345" x2="3.8711" y2="-3.6623" width="0.1016" layer="21"/>
<wire x1="3.8711" y1="-3.6623" x2="3.7318" y2="-3.8016" width="0.1016" layer="21"/>
<wire x1="3.7318" y1="-3.8016" x2="3.5369" y2="-3.913" width="0.1016" layer="21"/>
<wire x1="3.5369" y1="-3.913" x2="3.3558" y2="-4.0104" width="0.1016" layer="21"/>
<wire x1="3.3558" y1="-4.0104" x2="3.147" y2="-4.0522" width="0.1016" layer="21"/>
<wire x1="3.147" y1="-4.0522" x2="2.9799" y2="-4.1358" width="0.1016" layer="21"/>
<wire x1="2.9799" y1="-4.1358" x2="3.2444" y2="-3.6623" width="0.1016" layer="21"/>
<wire x1="3.2444" y1="-3.6623" x2="3.2584" y2="-3.5231" width="0.1016" layer="21"/>
<wire x1="5.8484" y1="-3.6623" x2="6.1965" y2="-3.6623" width="0.1016" layer="21"/>
<wire x1="6.1965" y1="-3.6623" x2="6.3636" y2="-3.718" width="0.1016" layer="21"/>
<wire x1="6.3636" y1="-3.718" x2="6.67" y2="-4.0383" width="0.1016" layer="21"/>
<wire x1="6.67" y1="-4.0383" x2="6.67" y2="-4.3725" width="0.1016" layer="21"/>
<wire x1="6.67" y1="-4.3725" x2="6.3915" y2="-4.5674" width="0.1016" layer="21"/>
<wire x1="6.3915" y1="-4.5674" x2="6.0991" y2="-4.7345" width="0.1016" layer="21"/>
<wire x1="6.0991" y1="-4.7345" x2="5.7509" y2="-4.8459" width="0.1016" layer="21"/>
<wire x1="5.7509" y1="-4.8459" x2="5.4167" y2="-4.9713" width="0.1016" layer="21"/>
<wire x1="5.4167" y1="-4.9713" x2="5.0825" y2="-4.9852" width="0.1016" layer="21"/>
<wire x1="5.0825" y1="-4.9852" x2="4.9572" y2="-4.9156" width="0.1016" layer="21"/>
<wire x1="4.9572" y1="-4.9156" x2="4.9711" y2="-4.7763" width="0.1016" layer="21"/>
<wire x1="4.9711" y1="-4.7763" x2="5.0965" y2="-4.3725" width="0.1016" layer="21"/>
<wire x1="5.0965" y1="-4.3725" x2="5.3332" y2="-4.0522" width="0.1016" layer="21"/>
<wire x1="5.3332" y1="-4.0522" x2="5.6952" y2="-3.7737" width="0.1016" layer="21"/>
<wire x1="5.6952" y1="-3.7737" x2="5.8484" y2="-3.6623" width="0.1016" layer="21"/>
<wire x1="6.0016" y1="-3.1889" x2="6.1408" y2="-3.2446" width="0.1016" layer="21"/>
<wire x1="6.1408" y1="-3.2446" x2="6.2383" y2="-3.356" width="0.1016" layer="21"/>
<wire x1="6.2383" y1="-3.356" x2="6.2522" y2="-3.4256" width="0.1016" layer="21"/>
<wire x1="6.2522" y1="-3.4256" x2="6.4472" y2="-3.4813" width="0.1016" layer="21"/>
<wire x1="6.4472" y1="-3.4813" x2="6.7257" y2="-3.6762" width="0.1016" layer="21"/>
<wire x1="6.7257" y1="-3.6762" x2="6.9624" y2="-3.8712" width="0.1016" layer="21"/>
<wire x1="6.9624" y1="-3.8712" x2="7.032" y2="-4.1358" width="0.1016" layer="21"/>
<wire x1="7.032" y1="-4.1358" x2="7.0042" y2="-4.3168" width="0.1016" layer="21"/>
<wire x1="7.0042" y1="-4.3168" x2="6.851" y2="-4.5953" width="0.1016" layer="21"/>
<wire x1="6.851" y1="-4.5953" x2="6.5864" y2="-4.8042" width="0.1016" layer="21"/>
<wire x1="6.5864" y1="-4.8042" x2="6.3915" y2="-4.9991" width="0.1016" layer="21"/>
<wire x1="6.3915" y1="-4.9991" x2="6.0294" y2="-5.0827" width="0.1016" layer="21"/>
<wire x1="6.0294" y1="-5.0827" x2="5.7649" y2="-5.2498" width="0.1016" layer="21"/>
<wire x1="5.7649" y1="-5.2498" x2="5.361" y2="-5.3055" width="0.1016" layer="21"/>
<wire x1="5.361" y1="-5.3055" x2="5.0408" y2="-5.3055" width="0.1016" layer="21"/>
<wire x1="5.0408" y1="-5.3055" x2="4.804" y2="-5.1523" width="0.1016" layer="21"/>
<wire x1="4.804" y1="-5.1523" x2="4.6648" y2="-4.8877" width="0.1016" layer="21"/>
<wire x1="4.6648" y1="-4.8877" x2="4.6787" y2="-4.6092" width="0.1016" layer="21"/>
<wire x1="4.6787" y1="-4.6092" x2="4.7483" y2="-4.275" width="0.1016" layer="21"/>
<wire x1="4.7483" y1="-4.275" x2="4.7901" y2="-4.1636" width="0.1016" layer="21"/>
<wire x1="4.7901" y1="-4.1636" x2="5.1661" y2="-3.7876" width="0.1016" layer="21"/>
<wire x1="5.1661" y1="-3.7876" x2="5.6952" y2="-3.342" width="0.1016" layer="21"/>
<wire x1="5.6952" y1="-3.342" x2="5.9877" y2="-3.1889" width="0.1016" layer="21"/>
<pad name="1" x="-11" y="8.746" drill="0.8" diameter="1.27"/>
<pad name="2" x="-11" y="6.746" drill="0.8" diameter="1.27"/>
<pad name="3" x="-11" y="4.746" drill="0.8" diameter="1.27"/>
<pad name="4" x="-11" y="2.746" drill="0.8" diameter="1.27"/>
<pad name="5" x="-11" y="0.746" drill="0.8" diameter="1.27"/>
<pad name="6" x="-11" y="-1.254" drill="0.8" diameter="1.27"/>
<pad name="7" x="-11" y="-3.254" drill="0.8" diameter="1.27"/>
<pad name="8" x="-11" y="-5.254" drill="0.8" diameter="1.27"/>
<pad name="9" x="-11" y="-7.254" drill="0.8" diameter="1.27"/>
<pad name="10" x="-11" y="-9.254" drill="0.8" diameter="1.27"/>
<pad name="11" x="11" y="-9.254" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="12" x="11" y="-7.254" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="13" x="11" y="-5.254" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="14" x="11" y="-3.254" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="15" x="11" y="-1.254" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="16" x="11" y="0.746" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="17" x="11" y="2.746" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="18" x="11" y="4.746" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="19" x="11" y="6.746" drill="0.8" diameter="1.27" rot="R180"/>
<pad name="20" x="11" y="8.746" drill="0.8" diameter="1.27" rot="R180"/>
<text x="-11.43" y="13.97" size="1.27" layer="25">&gt;NAME</text>
<text x="-11.43" y="-19.3" size="1.27" layer="27">&gt;VALUE</text>
<text x="-9.779" y="8.128" size="1.27" layer="21">1</text>
<text x="-9.779" y="6.1468" size="1.27" layer="21">2</text>
<text x="-9.779" y="4.1148" size="1.27" layer="21">3</text>
<text x="-9.779" y="2.1082" size="1.27" layer="21">4</text>
<text x="-9.779" y="0.127" size="1.27" layer="21">5</text>
<text x="-9.779" y="-1.905" size="1.27" layer="21">6</text>
<text x="-9.779" y="-3.8862" size="1.27" layer="21">7</text>
<text x="-9.779" y="-5.8928" size="1.27" layer="21">8</text>
<text x="-9.779" y="-7.8994" size="1.27" layer="21">9</text>
<text x="-9.779" y="-9.8806" size="1.27" layer="21">10</text>
<text x="8.001" y="-9.906" size="1.27" layer="21">11</text>
<text x="8.001" y="-8.001" size="1.27" layer="21">12</text>
<text x="8.001" y="-5.969" size="1.27" layer="21">13</text>
<text x="8.001" y="-3.937" size="1.27" layer="21">14</text>
<text x="8.001" y="-1.905" size="1.27" layer="21">15</text>
<text x="8.001" y="0.127" size="1.27" layer="21">16</text>
<text x="8.001" y="2.159" size="1.27" layer="21">17</text>
<text x="8.001" y="4.064" size="1.27" layer="21">18</text>
<text x="8.001" y="6.096" size="1.27" layer="21">19</text>
<text x="8.001" y="8.128" size="1.27" layer="21">20</text>
</package>
</packages>
<symbols>
<symbol name="XBEE">
<wire x1="-12.7" y1="27.94" x2="-12.7" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-25.4" x2="15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-25.4" x2="15.24" y2="27.94" width="0.254" layer="94"/>
<wire x1="15.24" y1="27.94" x2="-12.7" y2="27.94" width="0.254" layer="94"/>
<text x="-12.7" y="29.21" size="1.778" layer="95" font="vector">&gt;NAME</text>
<text x="-12.7" y="-27.94" size="1.778" layer="96" font="vector">&gt;VALUE</text>
<pin name="VCC" x="-15.24" y="25.4" length="short" direction="pwr"/>
<pin name="DOUT" x="-15.24" y="22.86" length="short" direction="out"/>
<pin name="DIN/!CONFIG" x="-15.24" y="20.32" length="short" direction="in"/>
<pin name="DIO12" x="-15.24" y="17.78" length="short"/>
<pin name="!RESET" x="-15.24" y="15.24" length="short" direction="in"/>
<pin name="RSSI/PWM/DIO10" x="-15.24" y="12.7" length="short" direction="out"/>
<pin name="!DTR!/SLEEP_RQ/DIO8" x="-15.24" y="5.08" length="short"/>
<pin name="GND" x="-15.24" y="2.54" length="short" direction="pwr"/>
<pin name="DIO4" x="-15.24" y="0" length="short"/>
<pin name="!CTS!/DIO7" x="-15.24" y="-2.54" length="short"/>
<pin name="ON/!SLEEP" x="-15.24" y="-5.08" length="short" direction="out"/>
<pin name="VREF" x="-15.24" y="-7.62" length="short" direction="in"/>
<pin name="ASSOC/DIO5" x="-15.24" y="-10.16" length="short"/>
<pin name="!RTS!/DIO6" x="-15.24" y="-12.7" length="short"/>
<pin name="AD3/DIO3" x="-15.24" y="-15.24" length="short"/>
<pin name="AD2/DIO2" x="-15.24" y="-17.78" length="short"/>
<pin name="AD1/DIO1" x="-15.24" y="-20.32" length="short"/>
<pin name="AD0/DIO0" x="-15.24" y="-22.86" length="short"/>
<pin name="PWM1/DIO11" x="-15.24" y="10.16" length="short"/>
<pin name="[RESERVED]" x="-15.24" y="7.62" length="short" direction="nc"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="XBEE" prefix="XB">
<description>&lt;b&gt;XBee (TM) /XBee-PRO(TM) OEM RF Modules&lt;/b&gt;
&lt;p&gt;
Based on the original package by MaxStream, Inc
&lt;/p&gt;
&lt;p&gt;
Improvements to the package by Sten Feldman:
&lt;ul&gt;
&lt;li&gt;Connecting all the pins of the PRO variant&lt;/li&gt;
&lt;li&gt;Silkscreen updates for spacing and pin numbers&lt;/li&gt;
&lt;/ul&gt;
&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="XBEE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="XBEE">
<connects>
<connect gate="G$1" pin="!CTS!/DIO7" pad="12"/>
<connect gate="G$1" pin="!DTR!/SLEEP_RQ/DIO8" pad="9"/>
<connect gate="G$1" pin="!RESET" pad="5"/>
<connect gate="G$1" pin="!RTS!/DIO6" pad="16"/>
<connect gate="G$1" pin="AD0/DIO0" pad="20"/>
<connect gate="G$1" pin="AD1/DIO1" pad="19"/>
<connect gate="G$1" pin="AD2/DIO2" pad="18"/>
<connect gate="G$1" pin="AD3/DIO3" pad="17"/>
<connect gate="G$1" pin="ASSOC/DIO5" pad="15"/>
<connect gate="G$1" pin="DIN/!CONFIG" pad="3"/>
<connect gate="G$1" pin="DIO12" pad="4"/>
<connect gate="G$1" pin="DIO4" pad="11"/>
<connect gate="G$1" pin="DOUT" pad="2"/>
<connect gate="G$1" pin="GND" pad="10"/>
<connect gate="G$1" pin="ON/!SLEEP" pad="13"/>
<connect gate="G$1" pin="RSSI/PWM/DIO10" pad="6"/>
<connect gate="G$1" pin="VCC" pad="1"/>
<connect gate="G$1" pin="VREF" pad="14"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="XBP24-Z7UIT-004" constant="no"/>
<attribute name="OC_FARNELL" value="1751799" constant="no"/>
<attribute name="OC_NEWARK" value="34R5507" constant="no"/>
</technology>
</technologies>
</device>
<device name="-PRO" package="XBEE-PRO">
<connects>
<connect gate="G$1" pin="!CTS!/DIO7" pad="12"/>
<connect gate="G$1" pin="!DTR!/SLEEP_RQ/DIO8" pad="9"/>
<connect gate="G$1" pin="!RESET" pad="5"/>
<connect gate="G$1" pin="!RTS!/DIO6" pad="16"/>
<connect gate="G$1" pin="AD0/DIO0" pad="20"/>
<connect gate="G$1" pin="AD1/DIO1" pad="19"/>
<connect gate="G$1" pin="AD2/DIO2" pad="18"/>
<connect gate="G$1" pin="AD3/DIO3" pad="17"/>
<connect gate="G$1" pin="ASSOC/DIO5" pad="15"/>
<connect gate="G$1" pin="DIN/!CONFIG" pad="3"/>
<connect gate="G$1" pin="DIO12" pad="4"/>
<connect gate="G$1" pin="DIO4" pad="11"/>
<connect gate="G$1" pin="DOUT" pad="2"/>
<connect gate="G$1" pin="GND" pad="10"/>
<connect gate="G$1" pin="ON/!SLEEP" pad="13"/>
<connect gate="G$1" pin="PWM1/DIO11" pad="7"/>
<connect gate="G$1" pin="RSSI/PWM/DIO10" pad="6"/>
<connect gate="G$1" pin="VCC" pad="1"/>
<connect gate="G$1" pin="VREF" pad="14"/>
<connect gate="G$1" pin="[RESERVED]" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="XBP24-AWI-001" constant="no"/>
<attribute name="OC_FARNELL" value="1337916" constant="no"/>
<attribute name="OC_NEWARK" value="42M2667" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="A4L-LOC" device=""/>
<part name="BR1" library="parts" deviceset="DF005M" device=""/>
<part name="PS1" library="parts" deviceset="MGFS1R5243R3" device=""/>
<part name="XB1" library="xbee" deviceset="XBEE" device="-PRO"/>
<part name="Q1" library="parts" deviceset="BC548BTA" device=""/>
<part name="K1" library="parts" deviceset="APAN3103" device=""/>
<part name="D1" library="parts" deviceset="1N4004RLG" device=""/>
<part name="R1" library="parts" deviceset="RN55D1801FB14" device=""/>
<part name="Q2" library="parts" deviceset="BC548BTA" device=""/>
<part name="K2" library="parts" deviceset="APAN3103" device=""/>
<part name="D2" library="parts" deviceset="1N4004RLG" device=""/>
<part name="R2" library="parts" deviceset="RN55D1801FB14" device=""/>
<part name="Q3" library="parts" deviceset="BC548BTA" device=""/>
<part name="K3" library="parts" deviceset="APAN3103" device=""/>
<part name="D3" library="parts" deviceset="1N4004RLG" device=""/>
<part name="R3" library="parts" deviceset="RN55D1801FB14" device=""/>
<part name="Q4" library="parts" deviceset="BC548BTA" device=""/>
<part name="K4" library="parts" deviceset="APAN3103" device=""/>
<part name="D4" library="parts" deviceset="1N4004RLG" device=""/>
<part name="R4" library="parts" deviceset="RN55D1801FB14" device=""/>
<part name="J1" library="parts" deviceset="39501-1002" device=""/>
<part name="J2" library="parts" deviceset="39501-1008" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0" smashed="yes">
<attribute name="DRAWING_NAME" x="217.17" y="15.24" size="2.54" layer="94"/>
<attribute name="LAST_DATE_TIME" x="217.17" y="10.16" size="2.286" layer="94"/>
<attribute name="SHEET" x="230.505" y="5.08" size="2.54" layer="94"/>
</instance>
<instance part="BR1" gate="G$1" x="12.7" y="50.8" smashed="yes" rot="R90">
<attribute name="NAME" x="5.08" y="69.85" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="7.62" y="69.85" size="1.778" layer="96" rot="R90" align="center-left"/>
</instance>
<instance part="PS1" gate="G$1" x="20.32" y="99.06" smashed="yes">
<attribute name="NAME" x="41.91" y="106.68" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="41.91" y="104.14" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="XB1" gate="G$1" x="38.1" y="154.94" smashed="yes" rot="R90">
<attribute name="NAME" x="8.89" y="142.24" size="1.778" layer="95" font="vector" rot="R90"/>
<attribute name="VALUE" x="66.04" y="142.24" size="1.778" layer="96" font="vector" rot="R90"/>
</instance>
<instance part="Q1" gate="G$1" x="63.5" y="91.44" smashed="yes" rot="R270">
<attribute name="NAME" x="64.77" y="77.47" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="62.23" y="77.47" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="K1" gate="G$1" x="76.2" y="63.5" smashed="yes">
<attribute name="NAME" x="85.09" y="71.12" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="85.09" y="68.58" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="D1" gate="G$1" x="53.34" y="63.5" smashed="yes" rot="R270">
<attribute name="NAME" x="58.42" y="52.07" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="55.88" y="52.07" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="R1" gate="G$1" x="63.5" y="93.98" smashed="yes" rot="R90">
<attribute name="NAME" x="67.31" y="100.33" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="69.85" y="100.33" size="1.778" layer="96" rot="R90" align="center-left"/>
</instance>
<instance part="Q2" gate="G$1" x="111.76" y="91.44" smashed="yes" rot="R270">
<attribute name="NAME" x="113.03" y="77.47" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="110.49" y="77.47" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="K2" gate="G$1" x="124.46" y="63.5" smashed="yes">
<attribute name="NAME" x="133.35" y="71.12" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="133.35" y="68.58" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="D2" gate="G$1" x="101.6" y="63.5" smashed="yes" rot="R270">
<attribute name="NAME" x="106.68" y="52.07" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="104.14" y="52.07" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="R2" gate="G$1" x="111.76" y="93.98" smashed="yes" rot="R90">
<attribute name="NAME" x="115.57" y="100.33" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="118.11" y="100.33" size="1.778" layer="96" rot="R90" align="center-left"/>
</instance>
<instance part="Q3" gate="G$1" x="160.02" y="91.44" smashed="yes" rot="R270">
<attribute name="NAME" x="161.29" y="77.47" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="158.75" y="77.47" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="K3" gate="G$1" x="172.72" y="63.5" smashed="yes">
<attribute name="NAME" x="181.61" y="71.12" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="181.61" y="68.58" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="D3" gate="G$1" x="149.86" y="63.5" smashed="yes" rot="R270">
<attribute name="NAME" x="154.94" y="52.07" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="152.4" y="52.07" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="R3" gate="G$1" x="160.02" y="93.98" smashed="yes" rot="R90">
<attribute name="NAME" x="163.83" y="100.33" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="166.37" y="100.33" size="1.778" layer="96" rot="R90" align="center-left"/>
</instance>
<instance part="Q4" gate="G$1" x="208.28" y="91.44" smashed="yes" rot="R270">
<attribute name="NAME" x="209.55" y="77.47" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="207.01" y="77.47" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="K4" gate="G$1" x="220.98" y="63.5" smashed="yes">
<attribute name="NAME" x="229.87" y="71.12" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="229.87" y="68.58" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="D4" gate="G$1" x="198.12" y="63.5" smashed="yes" rot="R270">
<attribute name="NAME" x="203.2" y="52.07" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="200.66" y="52.07" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="R4" gate="G$1" x="208.28" y="93.98" smashed="yes" rot="R90">
<attribute name="NAME" x="212.09" y="100.33" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="214.63" y="100.33" size="1.778" layer="96" rot="R90" align="center-left"/>
</instance>
<instance part="J1" gate="G$1" x="15.24" y="45.72" smashed="yes" rot="R270">
<attribute name="NAME" x="17.78" y="29.21" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="15.24" y="29.21" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
<instance part="J2" gate="G$1" x="43.18" y="45.72" smashed="yes" rot="R270">
<attribute name="NAME" x="45.72" y="29.21" size="1.778" layer="95" rot="R270" align="center-left"/>
<attribute name="VALUE" x="43.18" y="29.21" size="1.778" layer="96" rot="R270" align="center-left"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<pinref part="Q1" gate="G$1" pin="B"/>
<wire x1="63.5" y1="93.98" x2="63.5" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="E"/>
<pinref part="PS1" gate="G$1" pin="-VOUT"/>
<wire x1="20.32" y1="91.44" x2="20.32" y2="86.36" width="0.1524" layer="91"/>
<wire x1="20.32" y1="86.36" x2="55.88" y2="86.36" width="0.1524" layer="91"/>
<wire x1="55.88" y1="86.36" x2="55.88" y2="81.28" width="0.1524" layer="91"/>
<label x="55.88" y="88.9" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="Q2" gate="G$1" pin="E"/>
<wire x1="99.06" y1="86.36" x2="104.14" y2="86.36" width="0.1524" layer="91"/>
<wire x1="104.14" y1="86.36" x2="104.14" y2="81.28" width="0.1524" layer="91"/>
<label x="104.14" y="88.9" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="Q3" gate="G$1" pin="E"/>
<wire x1="147.32" y1="86.36" x2="152.4" y2="86.36" width="0.1524" layer="91"/>
<wire x1="152.4" y1="86.36" x2="152.4" y2="81.28" width="0.1524" layer="91"/>
<label x="152.4" y="88.9" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="Q4" gate="G$1" pin="E"/>
<wire x1="195.58" y1="86.36" x2="200.66" y2="86.36" width="0.1524" layer="91"/>
<wire x1="200.66" y1="86.36" x2="200.66" y2="81.28" width="0.1524" layer="91"/>
<label x="200.66" y="88.9" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<wire x1="43.18" y1="45.72" x2="43.18" y2="58.42" width="0.1524" layer="91"/>
<label x="43.18" y="50.8" size="1.778" layer="95" rot="R90"/>
<pinref part="J2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="C"/>
<pinref part="K1" gate="G$1" pin="COIL_2"/>
<wire x1="71.12" y1="81.28" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
<wire x1="71.12" y1="60.96" x2="76.2" y2="60.96" width="0.1524" layer="91"/>
<pinref part="D1" gate="G$1" pin="A"/>
<wire x1="53.34" y1="48.26" x2="71.12" y2="48.26" width="0.1524" layer="91"/>
<wire x1="71.12" y1="48.26" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
<junction x="71.12" y="60.96"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="D1" gate="G$1" pin="K"/>
<pinref part="K1" gate="G$1" pin="COIL_1"/>
<wire x1="53.34" y1="63.5" x2="76.2" y2="63.5" width="0.1524" layer="91"/>
<wire x1="53.34" y1="83.82" x2="53.34" y2="63.5" width="0.1524" layer="91"/>
<junction x="53.34" y="63.5"/>
<pinref part="PS1" gate="G$1" pin="+VOUT"/>
<wire x1="20.32" y1="93.98" x2="17.78" y2="93.98" width="0.1524" layer="91"/>
<wire x1="17.78" y1="93.98" x2="17.78" y2="83.82" width="0.1524" layer="91"/>
<wire x1="17.78" y1="83.82" x2="53.34" y2="83.82" width="0.1524" layer="91"/>
<label x="48.26" y="86.36" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="D2" gate="G$1" pin="K"/>
<pinref part="K2" gate="G$1" pin="COIL_1"/>
<wire x1="101.6" y1="63.5" x2="124.46" y2="63.5" width="0.1524" layer="91"/>
<wire x1="101.6" y1="83.82" x2="101.6" y2="63.5" width="0.1524" layer="91"/>
<junction x="101.6" y="63.5"/>
<wire x1="91.44" y1="83.82" x2="101.6" y2="83.82" width="0.1524" layer="91"/>
<label x="96.52" y="86.36" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="D3" gate="G$1" pin="K"/>
<pinref part="K3" gate="G$1" pin="COIL_1"/>
<wire x1="149.86" y1="63.5" x2="172.72" y2="63.5" width="0.1524" layer="91"/>
<wire x1="149.86" y1="83.82" x2="149.86" y2="63.5" width="0.1524" layer="91"/>
<junction x="149.86" y="63.5"/>
<wire x1="139.7" y1="83.82" x2="149.86" y2="83.82" width="0.1524" layer="91"/>
<label x="144.78" y="86.36" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="D4" gate="G$1" pin="K"/>
<pinref part="K4" gate="G$1" pin="COIL_1"/>
<wire x1="198.12" y1="63.5" x2="220.98" y2="63.5" width="0.1524" layer="91"/>
<wire x1="198.12" y1="83.82" x2="198.12" y2="63.5" width="0.1524" layer="91"/>
<junction x="198.12" y="63.5"/>
<wire x1="187.96" y1="83.82" x2="198.12" y2="83.82" width="0.1524" layer="91"/>
<label x="193.04" y="86.36" size="1.778" layer="95" rot="R180"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="BR1" gate="G$1" pin="-"/>
<pinref part="PS1" gate="G$1" pin="-VIN"/>
<wire x1="12.7" y1="73.66" x2="12.7" y2="99.06" width="0.1524" layer="91"/>
<wire x1="12.7" y1="99.06" x2="20.32" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="BR1" gate="G$1" pin="+"/>
<pinref part="PS1" gate="G$1" pin="+VIN"/>
<wire x1="15.24" y1="73.66" x2="15.24" y2="96.52" width="0.1524" layer="91"/>
<wire x1="15.24" y1="96.52" x2="20.32" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="COM1" class="0">
<segment>
<wire x1="38.1" y1="45.72" x2="38.1" y2="58.42" width="0.1524" layer="91"/>
<label x="38.1" y="45.72" size="1.778" layer="95" rot="R90"/>
<pinref part="J2" gate="G$1" pin="3"/>
</segment>
<segment>
<pinref part="K1" gate="G$1" pin="COM"/>
<wire x1="76.2" y1="55.88" x2="76.2" y2="35.56" width="0.1524" layer="91"/>
<label x="76.2" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="K2" gate="G$1" pin="COM"/>
<wire x1="124.46" y1="55.88" x2="124.46" y2="35.56" width="0.1524" layer="91"/>
<label x="124.46" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="ACT1" class="0">
<segment>
<wire x1="35.56" y1="45.72" x2="35.56" y2="58.42" width="0.1524" layer="91"/>
<label x="35.56" y="45.72" size="1.778" layer="95" rot="R90"/>
<pinref part="J2" gate="G$1" pin="4"/>
</segment>
<segment>
<pinref part="K1" gate="G$1" pin="NO"/>
<wire x1="76.2" y1="58.42" x2="73.66" y2="58.42" width="0.1524" layer="91"/>
<wire x1="73.66" y1="58.42" x2="73.66" y2="35.56" width="0.1524" layer="91"/>
<label x="73.66" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="ACT2" class="0">
<segment>
<wire x1="33.02" y1="45.72" x2="33.02" y2="58.42" width="0.1524" layer="91"/>
<label x="31.242" y="52.07" size="1.778" layer="95" rot="R270"/>
<pinref part="J2" gate="G$1" pin="5"/>
</segment>
<segment>
<pinref part="K2" gate="G$1" pin="NO"/>
<wire x1="124.46" y1="58.42" x2="121.92" y2="58.42" width="0.1524" layer="91"/>
<wire x1="121.92" y1="58.42" x2="121.92" y2="35.56" width="0.1524" layer="91"/>
<label x="121.92" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="COM2" class="0">
<segment>
<wire x1="30.48" y1="45.72" x2="30.48" y2="58.42" width="0.1524" layer="91"/>
<label x="30.48" y="45.72" size="1.778" layer="95" rot="R90"/>
<pinref part="J2" gate="G$1" pin="6"/>
</segment>
<segment>
<pinref part="K3" gate="G$1" pin="COM"/>
<wire x1="172.72" y1="55.88" x2="172.72" y2="35.56" width="0.1524" layer="91"/>
<label x="172.72" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="K4" gate="G$1" pin="COM"/>
<wire x1="220.98" y1="55.88" x2="220.98" y2="35.56" width="0.1524" layer="91"/>
<label x="220.98" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="ACT3" class="0">
<segment>
<wire x1="27.94" y1="45.72" x2="27.94" y2="58.42" width="0.1524" layer="91"/>
<label x="26.162" y="52.07" size="1.778" layer="95" rot="R270"/>
<pinref part="J2" gate="G$1" pin="7"/>
</segment>
<segment>
<pinref part="K3" gate="G$1" pin="NO"/>
<wire x1="172.72" y1="58.42" x2="170.18" y2="58.42" width="0.1524" layer="91"/>
<wire x1="170.18" y1="58.42" x2="170.18" y2="35.56" width="0.1524" layer="91"/>
<label x="170.18" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="ACT4" class="0">
<segment>
<wire x1="25.4" y1="45.72" x2="25.4" y2="58.42" width="0.1524" layer="91"/>
<label x="23.622" y="52.07" size="1.778" layer="95" rot="R270"/>
<pinref part="J2" gate="G$1" pin="8"/>
</segment>
<segment>
<pinref part="K4" gate="G$1" pin="NO"/>
<wire x1="220.98" y1="58.42" x2="218.44" y2="58.42" width="0.1524" layer="91"/>
<wire x1="218.44" y1="58.42" x2="218.44" y2="35.56" width="0.1524" layer="91"/>
<label x="218.44" y="35.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="DIO0" class="0">
<segment>
<wire x1="40.64" y1="45.72" x2="40.64" y2="58.42" width="0.1524" layer="91"/>
<label x="40.64" y="45.72" size="1.778" layer="95" rot="R90"/>
<pinref part="J2" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="XB1" gate="G$1" pin="AD0/DIO0"/>
<wire x1="60.96" y1="139.7" x2="60.96" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<pinref part="Q2" gate="G$1" pin="B"/>
<wire x1="111.76" y1="93.98" x2="111.76" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="Q2" gate="G$1" pin="C"/>
<pinref part="K2" gate="G$1" pin="COIL_2"/>
<wire x1="119.38" y1="81.28" x2="119.38" y2="60.96" width="0.1524" layer="91"/>
<wire x1="119.38" y1="60.96" x2="124.46" y2="60.96" width="0.1524" layer="91"/>
<pinref part="D2" gate="G$1" pin="A"/>
<wire x1="101.6" y1="48.26" x2="119.38" y2="48.26" width="0.1524" layer="91"/>
<wire x1="119.38" y1="48.26" x2="119.38" y2="60.96" width="0.1524" layer="91"/>
<junction x="119.38" y="60.96"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="1"/>
<pinref part="Q3" gate="G$1" pin="B"/>
<wire x1="160.02" y1="93.98" x2="160.02" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="Q3" gate="G$1" pin="C"/>
<pinref part="K3" gate="G$1" pin="COIL_2"/>
<wire x1="167.64" y1="81.28" x2="167.64" y2="60.96" width="0.1524" layer="91"/>
<wire x1="167.64" y1="60.96" x2="172.72" y2="60.96" width="0.1524" layer="91"/>
<pinref part="D3" gate="G$1" pin="A"/>
<wire x1="149.86" y1="48.26" x2="167.64" y2="48.26" width="0.1524" layer="91"/>
<wire x1="167.64" y1="48.26" x2="167.64" y2="60.96" width="0.1524" layer="91"/>
<junction x="167.64" y="60.96"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="R4" gate="G$1" pin="1"/>
<pinref part="Q4" gate="G$1" pin="B"/>
<wire x1="208.28" y1="93.98" x2="208.28" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="Q4" gate="G$1" pin="C"/>
<pinref part="K4" gate="G$1" pin="COIL_2"/>
<wire x1="215.9" y1="81.28" x2="215.9" y2="60.96" width="0.1524" layer="91"/>
<wire x1="215.9" y1="60.96" x2="220.98" y2="60.96" width="0.1524" layer="91"/>
<pinref part="D4" gate="G$1" pin="A"/>
<wire x1="198.12" y1="48.26" x2="215.9" y2="48.26" width="0.1524" layer="91"/>
<wire x1="215.9" y1="48.26" x2="215.9" y2="60.96" width="0.1524" layer="91"/>
<junction x="215.9" y="60.96"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="63.5" y1="111.76" x2="63.5" y2="116.84" width="0.1524" layer="91"/>
<pinref part="XB1" gate="G$1" pin="PWM1/DIO11"/>
<wire x1="63.5" y1="116.84" x2="27.94" y2="116.84" width="0.1524" layer="91"/>
<wire x1="27.94" y1="116.84" x2="27.94" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="111.76" y1="119.38" x2="111.76" y2="111.76" width="0.1524" layer="91"/>
<pinref part="XB1" gate="G$1" pin="AD1/DIO1"/>
<wire x1="111.76" y1="119.38" x2="58.42" y2="119.38" width="0.1524" layer="91"/>
<wire x1="58.42" y1="119.38" x2="58.42" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="160.02" y1="121.92" x2="160.02" y2="111.76" width="0.1524" layer="91"/>
<pinref part="XB1" gate="G$1" pin="AD2/DIO2"/>
<wire x1="160.02" y1="121.92" x2="55.88" y2="121.92" width="0.1524" layer="91"/>
<wire x1="55.88" y1="121.92" x2="55.88" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="208.28" y1="124.46" x2="208.28" y2="111.76" width="0.1524" layer="91"/>
<pinref part="XB1" gate="G$1" pin="DIO4"/>
<wire x1="208.28" y1="124.46" x2="38.1" y2="124.46" width="0.1524" layer="91"/>
<wire x1="38.1" y1="124.46" x2="38.1" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="BR1" gate="G$1" pin="~_1"/>
<wire x1="12.7" y1="50.8" x2="12.7" y2="45.72" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="BR1" gate="G$1" pin="~_2"/>
<wire x1="15.24" y1="50.8" x2="15.24" y2="45.72" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
