//
//  DetectorConstruction.cc 2013-09-04  Maxime Chauvin
//  SAS included by Merlin Kole 2013-10-22
//  Polarimeter rotation by Maxime Chauvin 2013-12-18
//

#include "DetectorConstruction.hh"
#include "StructureConstruction.hh"
#include "TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

DetectorConstruction::DetectorConstruction()
{
  // create commands for interactive definition of the detector
  detectorMessenger = new DetectorMessenger(this);

  // define some rotation matrices
  DefineRotations();
}

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager * nist_manager = G4NistManager::Instance();
  G4Material * air_1atm = nist_manager->FindOrBuildMaterial("G4_AIR");
  G4Material * air_3hPa = nist_manager->BuildMaterialWithNewDensity("Air_3hPa","G4_AIR", 0.0041*kg/m3);
  G4Material * atmos = nist_manager->BuildMaterialWithNewDensity("Atmosphere","G4_AIR", 5.655*g/cm3); // average over 13th and 14th
  //G4Material * atmos = nist_manager->BuildMaterialWithNewDensity("Atmosphere","G4_AIR", 4.89*g/cm3); // 2013-07-13 12h00
  G4Material * Al = nist_manager->FindOrBuildMaterial("G4_Al");
  G4Material * Sn = nist_manager->FindOrBuildMaterial("G4_Sn");
  G4Material * Pb = nist_manager->FindOrBuildMaterial("G4_Pb");
  G4Material * BGO = nist_manager->FindOrBuildMaterial("G4_BGO");
  G4Material * PE = nist_manager->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material * EJ204 = nist_manager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

  //-------------------- Create the World Volume ----------------------------------
  const G4double WorldSize  = 600.0*cm; 
  G4Box* s_World = new G4Box("World", WorldSize/2, WorldSize/2, WorldSize/2);
  G4LogicalVolume* l_World = new G4LogicalVolume(s_World, air_3hPa, "World");
  G4VPhysicalVolume* p_World = new G4PVPlacement(0,	G4ThreeVector(), l_World, "World", NULL, false, 0);

  //-------------------- Include atmosphere ---------------------------------------
  //const G4String Atmosname = "Atmosphere";
  //G4Tubs* s_Atmos = new G4Tubs(Atmosname, 0.0*mm, 200.0*cm, 1./2*cm, 0.*deg, 360.*deg);
  //G4LogicalVolume* l_Atmos = new G4LogicalVolume(s_Atmos, atmos, Atmosname);
  //new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,200.0*cm), l_Atmos, Atmosname, l_World, false, 0);

  //-------------------- Create POGO mother volume --------------------------------
  G4Box* s_Pogo = new G4Box("Pogo", 95*cm,95*cm,95*cm);
  G4LogicalVolume* l_Pogo = new G4LogicalVolume(s_Pogo, air_3hPa, "Pogo");
  p_Pogo = new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,0.0*cm), l_Pogo, "Pogo", l_World, false, 0);

  //-------------------- Create Polarimeter mother volume -------------------------
  G4Tubs* s_Polarimeter = new G4Tubs("Polarimeter", 0.0*cm, 435.0/2.0*mm, 88.45*cm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Polarimeter = new G4LogicalVolume(s_Polarimeter, air_1atm, "Polarimeter");
  p_Polarimeter = new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,0.0*cm), l_Polarimeter, "Polarimeter", l_Pogo, false, 0);

  //-------------------- Now include PVA, RFA, STM, STR and AMU -------------------
  //new StructureConstruction(l_Pogo, l_Polarimeter);

  //-------------------- Now construct the polarimeter ----------------------------
  // PDC mother volume
  const G4String PDCName = "PDCUnit";
  const G4double PDCZ[2] = {-22.0*cm,80.517*cm};
  const G4double PDCInner[2] = {0.0*cm,0.0*cm};
  const G4double PDCOuter[2] = {1.5*cm,1.5*cm};
  G4Polyhedra* s_PDC = new G4Polyhedra(PDCName, 0.*deg, 360.*deg, 6, 2, PDCZ, PDCInner, PDCOuter);
  G4LogicalVolume* l_PDC = new G4LogicalVolume(s_PDC, air_1atm, PDCName);

      // top plastic cap
      const G4String PlasticCapName = "PlasticCap";					      
      const G4double PlasticCapZ[4] = {59.017*cm,60.017*cm,60.017*cm,60.517*cm};
      const G4double PlasticCapInner[4] = {1.367*cm,1.367*cm,1.167*cm,1.167*cm};
      const G4double PlasticCapOuter[4] = {1.467*cm,1.467*cm,1.467*cm,1.467*cm};
      G4Polyhedra* s_PlasticCap = new G4Polyhedra(PlasticCapName, 0.*deg, 360.*deg, 6, 4, PlasticCapZ, PlasticCapInner, PlasticCapOuter);
      G4LogicalVolume* l_PlasticCap = new G4LogicalVolume(s_PlasticCap, PE, PlasticCapName);
      //new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l_PlasticCap, PlasticCapName, l_PDC, false, 0);

      // slow scintillator
      const G4String SlowName = "SlowScintillator";
      const G4double SlowZ[2] = {0.0*cm,60.0*cm};
      const G4double SlowInner[2] = {1.15*cm,1.15*cm};
      const G4double SlowOuter[2] = {1.35*cm,1.35*cm};
      G4Polyhedra* s_Slow = new G4Polyhedra(SlowName, 0.*deg, 360.*deg, 6, 2, SlowZ, SlowInner, SlowOuter);
      G4LogicalVolume* l_Slow = new G4LogicalVolume(s_Slow, EJ204, SlowName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l_Slow, SlowName, l_PDC, false, 0);

      // fast scintillator
      const G4String FastName = "FastScintillator";
      const G4double FastZ[2] = {0.0*cm,20.0*cm};
      const G4double FastInner[2] = {0.0*cm,0.0*cm};
      const G4double FastOuter[2] = {1.3875*cm,1.3875*cm};
      G4Polyhedra* s_Fast = new G4Polyhedra(FastName, 0.*deg, 360.*deg, 6, 2, FastZ, FastInner, FastOuter);
      G4LogicalVolume* l_Fast = new G4LogicalVolume(s_Fast, EJ204, FastName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,0.0*cm), l_Fast, FastName, l_PDC, false, 0);

      // passive collimator Sn + Pb foil
      const G4String CollName = "PassiveCollimator";
      const G4double Sn1CollZ[6] = {-0.5*cm,0.0*cm,0.0*cm,0.005*cm,0.005*cm,59.0*cm};
      const G4double Sn1CollInner[6] = {1.3875*cm,1.3875*cm,1.35*cm,1.35*cm,1.35*cm,1.35*cm};
      const G4double Sn1CollOuter[6] = {1.3925*cm,1.3925*cm,1.3925*cm,1.3925*cm,1.355*cm,1.355*cm};
      G4Polyhedra* s1_SnColl = new G4Polyhedra(CollName, 0.*deg, 60.*deg, 1, 6, Sn1CollZ, Sn1CollInner, Sn1CollOuter); // the Sn foil has one additionnal side
      G4LogicalVolume* l1_SnColl = new G4LogicalVolume(s1_SnColl, Sn, CollName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l1_SnColl, CollName, l_PDC, false, 0);
      const G4double Sn2CollZ[6] = {-0.5*cm,0.005*cm,0.005*cm,0.01*cm,0.01*cm,59.0*cm};
      const G4double Sn2CollInner[6] = {1.3925*cm,1.3925*cm,1.355*cm,1.355*cm,1.355*cm,1.355*cm};
      const G4double Sn2CollOuter[6] = {1.3975*cm,1.3975*cm,1.3975*cm,1.3975*cm,1.36*cm,1.36*cm};
      G4Polyhedra* s2_SnColl = new G4Polyhedra(CollName, 0.*deg, 360.*deg, 6, 6, Sn2CollZ, Sn2CollInner, Sn2CollOuter);
      G4LogicalVolume* l2_SnColl = new G4LogicalVolume(s2_SnColl, Sn, CollName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l2_SnColl, CollName, l_PDC, false, 0);

      const G4double PbCollZ[2] = {0.5*cm,59.0*cm};
      const G4double PbCollInner[2] = {1.36*cm,1.36*cm};
      const G4double PbCollOuter[2] = {1.365*cm,1.365*cm};
      G4Polyhedra* s_PbColl = new G4Polyhedra(CollName, 0.*deg, 360.*deg, 6, 2, PbCollZ, PbCollInner, PbCollOuter);
      G4LogicalVolume* l_PbColl = new G4LogicalVolume(s_PbColl, Pb, CollName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l_PbColl, CollName, l_PDC, false, 0);

      // heat shrink
      const G4String HeatShrinkName = "HeatShrink";
      const G4double HeatShrinkZ[18] = {0.0*cm,19.483*cm,19.483*cm,19.5*cm,19.5*cm,20.01*cm,20.01*cm,20.027*cm,20.027*cm,20.483*cm,20.483*cm,20.5*cm,20.5*cm,79.0*cm,79.0*cm,79.017*cm,79.017*cm,80.0*cm};
      const G4double HeatShrinkInner[18] = {1.3875*cm,1.3875*cm,1.3875*cm,1.3875*cm,1.3975*cm,1.3975*cm,1.360*cm,1.360*cm,1.360*cm,1.360*cm,1.360*cm,1.360*cm, 1.365*cm,1.365*cm,1.35*cm,1.35*cm,1.35*cm,1.35*cm};
      const G4double HeatShrinkOuter[18] = {1.4045*cm,1.4045*cm,1.4145*cm,1.4145*cm,1.4145*cm,1.4145*cm,1.4145*cm,1.4145*cm,1.377*cm,1.377*cm,1.382*cm,1.382*cm,1.382*cm,1.382*cm,1.382*cm,1.382*cm,1.367*cm,1.367*cm};
      G4Polyhedra* s_HeatShrink = new G4Polyhedra(HeatShrinkName, 0.*deg, 360.*deg, 6, 18, HeatShrinkZ, HeatShrinkInner, HeatShrinkOuter);
      G4LogicalVolume* l_HeatShrink = new G4LogicalVolume(s_HeatShrink, PE, HeatShrinkName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,0.0*cm), l_HeatShrink, HeatShrinkName, l_PDC, false, 0);

      // bottom BGO
      const G4String BGObottomName = "BGObottom";
      const G4double BGOZ[2] = {0.0*cm,4.0*cm};
      const G4double BGOInner[2] = {0.0*cm,0.0*cm};
      const G4double BGOOuter[2] = {1.425*cm,1.425*cm};
      G4Polyhedra* s1_BGO = new G4Polyhedra("s1_BGO", 0.*deg, 360.*deg, 6, 2, BGOZ, BGOInner, BGOOuter);
      const G4double BGOCylinderZ[4] = {0.0*cm,1.2*cm,2.0*cm,4.0*cm};
      const G4double BGOCylinderInner[4] = {0.0*cm,0.0*cm,0.0*cm,0.0*cm};
      const G4double BGOCylinderOuter[4] = {1.15*cm,1.15*cm,1.612*cm,1.612*cm};
      G4Polycone* s2_BGO = new G4Polycone("s2_BGO", 0.*deg, 360.*deg, 4, BGOCylinderZ, BGOCylinderInner, BGOCylinderOuter);
      G4IntersectionSolid* s_BGObottom = new G4IntersectionSolid(BGObottomName, s1_BGO, s2_BGO);
      G4LogicalVolume* l_BGObottom = new G4LogicalVolume(s_BGObottom, BGO, BGObottomName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-4.0*cm), l_BGObottom, BGObottomName, l_PDC, false, 0);

      // PM Tube
      const G4String PMName = "PMTube";
      G4Tubs* s_PM = new G4Tubs(PMName, 0.*cm, 1.15*cm, 9.0*cm, 0.*deg, 360.*deg);
      G4LogicalVolume* l_PM = new G4LogicalVolume(s_PM, Al, PMName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-13.0*cm), l_PM, PMName, l_PDC, false, 0);


  // SAS edge mother volume
  const G4String SASedgeUnitName = "SASedgeUnit";
  G4Box* s1_SASedgeUnit = new G4Box("SASedgeUnit_box", 2.0*cm, 1.465*cm, 39.6*cm);
  G4Tubs* s2_SASedgeUnit = new G4Tubs("SASedgeUnit_cyl", 0.*cm, 1.691*cm, 39.6*cm, -60.0*deg, 120.0*deg);
  G4UnionSolid* s_SASedgeUnit = new G4UnionSolid(SASedgeUnitName, s1_SASedgeUnit, s2_SASedgeUnit, 0, G4ThreeVector(-2.845*cm,0.0*cm,0.0*cm));
  G4LogicalVolume* l_SASedgeUnit = new G4LogicalVolume(s_SASedgeUnit, air_1atm, SASedgeUnitName);

      // SAS edge back bone
      const G4String SASedgeBoneName = "SASedgeBone";
      G4Box* s_SASedgeBone = new G4Box(SASedgeBoneName, 0.49*cm, 1.465*cm, 30.0*cm);
      G4LogicalVolume* l_SASedgeBone = new G4LogicalVolume(s_SASedgeBone, Al, SASedgeBoneName);  
      new G4PVPlacement(0, G4ThreeVector(1.5*cm,0.0*cm,9.6*cm), l_SASedgeBone, SASedgeBoneName, l_SASedgeUnit, false, 0);

      // SAS edge
      const G4String SASedgeName = "SASedge";
      G4Box* s1_SASedge = new G4Box("SASedge_box", 1.5*cm, 1.465*cm, 30.0*cm);
      G4Tubs* s2_SASedge = new G4Tubs("SASedge_cyl", 0.*cm, 1.691*cm, 30.0*cm, -60.0*deg, 120.0*deg);
      G4UnionSolid* s_SASedge = new G4UnionSolid(SASedgeName, s1_SASedge, s2_SASedge, 0, G4ThreeVector(-2.345*cm,0.0*cm,0.0*cm));
      G4LogicalVolume* l_SASedge = new G4LogicalVolume(s_SASedge, BGO, SASedgeName);  
      new G4PVPlacement(0, G4ThreeVector(-0.5*cm,0.0*cm,9.6*cm), l_SASedge, SASedgeName, l_SASedgeUnit, false, 0);

      // SAS bottom edge
      const G4String SASbottomName = "SASbottom";
      G4Tubs* s_SASbottom = new G4Tubs(SASbottomName, 0.*cm, 1.15*cm, 0.6*cm, 0.*deg, 360.*deg);
      G4LogicalVolume* l_SASbottom = new G4LogicalVolume(s_SASbottom, BGO, SASbottomName);
      new G4PVPlacement(0, G4ThreeVector(-0.5*cm,0.0*cm,-21.0*cm), l_SASbottom, SASbottomName, l_SASedgeUnit, false, 0);

      // SAS PMT
      new G4PVPlacement(0, G4ThreeVector(-0.5*cm,0.0*cm,-30.6*cm), l_PM, PMName, l_SASedgeUnit, false, 0);

  // SAS corner mother volume
  const G4String SAScornerUnitName = "SAScornerUnit";
  G4Trap* s1_SAScornerUnit = new G4Trap("SAScornerUnit_trap", 39.6*cm, 0, 0, 1.73*cm, 0.93*cm, 2.93*cm, 0, 1.73*cm, 0.93*cm, 2.93*cm, 0);
  G4Tubs* s2_SAScornerUnit = new G4Tubs("SAScornerUnit_cyl", 0, 3.38*cm, 39.6*cm, 210.0*deg, 120.0*deg);
  G4UnionSolid* s_SAScornerUnit = new G4UnionSolid(SAScornerUnitName, s1_SAScornerUnit, s2_SAScornerUnit, 0, G4ThreeVector(0, 3.42*cm, 0));
  G4LogicalVolume* l_SAScornerUnit = new G4LogicalVolume(s_SAScornerUnit, air_1atm, SAScornerUnitName);

      // SAS corner back bone
      const G4String SAScornerBoneName = "SAScornerBone";
      G4Box* s1_SAScornerBone = new G4Box(SAScornerBoneName, 0.49*cm, 1.69*cm, 30.0*cm);
      G4UnionSolid* s_SAScornerBone = new G4UnionSolid(SAScornerBoneName, s1_SAScornerBone, s1_SAScornerBone, zRot60, G4ThreeVector(-1.2136*cm,-2.102*cm,0.0*cm));
      G4LogicalVolume* l_SAScornerBone = new G4LogicalVolume(s_SAScornerBone, Al, SAScornerBoneName);  
      new G4PVPlacement(zRot240, G4ThreeVector(-1.2136*cm,2.142*cm,9.6*cm), l_SAScornerBone, SAScornerBoneName, l_SAScornerUnit, false, 0);

      // SAS corner
      const G4String SAScornerName = "SAScorner";
      G4Trap* s1_SAScorner = new G4Trap("SAScorner_trap", 30.0*cm, 0, 0, 1.3*cm, 0.93*cm, 2.43*cm, 0, 1.3*cm, 0.93*cm, 2.43 *cm, 0);
      G4Tubs* s2_SAScorner = new G4Tubs("SAScorner_cyl", 0, 2.81*cm, 30.0*cm, 210.0*deg, 120.0*deg);
      G4UnionSolid* s_SAScorner = new G4UnionSolid(SAScornerName, s1_SAScorner, s2_SAScorner, 0, G4ThreeVector(0, 2.705*cm, 0));
      G4LogicalVolume* l_SAScorner = new G4LogicalVolume(s_SAScorner, BGO, SAScornerName);
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,-0.433*cm,9.6*cm), l_SAScorner, SAScornerName, l_SAScornerUnit, false, 0);

      // SAS bottom corner
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.20*cm,-21.0*cm), l_SASbottom, SASbottomName, l_SAScornerUnit, false, 0);

      // PMT corner
      new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.20*cm,-30.6*cm), l_PM, PMName, l_SAScornerUnit, false, 0);

  // place 61 PDC units
  new G4PVPlacement(      0, G4ThreeVector(  0.0000*mm,     0.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 0);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,    30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 1);
  //new G4PVPlacement(zRot120, G4ThreeVector( 25.9808*mm,    15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 2);
  //new G4PVPlacement(zRot180, G4ThreeVector( 25.9808*mm,   -15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 3);
  //new G4PVPlacement(zRot240, G4ThreeVector(  0.0000*mm,   -30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 4);
  //new G4PVPlacement(zRot300, G4ThreeVector(-25.9808*mm,   -15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 5);
  //new G4PVPlacement(      0, G4ThreeVector(-25.9808*mm,    15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 6);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,    60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 7);
  //new G4PVPlacement(zRot120, G4ThreeVector( 25.9808*mm,    45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 8);
  //new G4PVPlacement(zRot180, G4ThreeVector( 51.9615*mm,    30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 9);
  //new G4PVPlacement(zRot240, G4ThreeVector( 51.9615*mm,     0.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 10);
  //new G4PVPlacement(zRot300, G4ThreeVector( 51.9615*mm,   -30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 11);
  //new G4PVPlacement(      0, G4ThreeVector( 25.9808*mm,   -45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 12);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,   -60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 13);
  //new G4PVPlacement(zRot120, G4ThreeVector(-25.9808*mm,   -45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 14);
  //new G4PVPlacement(zRot180, G4ThreeVector(-51.9615*mm,   -30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 15);
  //new G4PVPlacement(zRot240, G4ThreeVector(-51.9615*mm,     0.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 16);
  //new G4PVPlacement(zRot300, G4ThreeVector(-51.9615*mm,    30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 17);
  //new G4PVPlacement(      0, G4ThreeVector(-25.9808*mm,    45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 18);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,    90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 19);
  //new G4PVPlacement(zRot120, G4ThreeVector( 25.9808*mm,    75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 20);
  //new G4PVPlacement(zRot180, G4ThreeVector( 51.9615*mm,    60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 21);
  //new G4PVPlacement(zRot240, G4ThreeVector( 77.9423*mm,    45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 22);
  //new G4PVPlacement(zRot300, G4ThreeVector( 77.9423*mm,    15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 23);
  //new G4PVPlacement(      0, G4ThreeVector( 77.9423*mm,   -15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 24);
  //new G4PVPlacement( zRot60, G4ThreeVector( 77.9423*mm,   -45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 25);
  //new G4PVPlacement(zRot120, G4ThreeVector( 51.9615*mm,   -60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 26);
  //new G4PVPlacement(zRot180, G4ThreeVector( 25.9808*mm,   -75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 27);
  //new G4PVPlacement(zRot240, G4ThreeVector(  0.0000*mm,   -90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 28);
  //new G4PVPlacement(zRot300, G4ThreeVector(-25.9808*mm,   -75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 29);
  //new G4PVPlacement(      0, G4ThreeVector(-51.9615*mm,   -60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 30);
  //new G4PVPlacement( zRot60, G4ThreeVector(-77.9423*mm,   -45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 31);
  //new G4PVPlacement(zRot120, G4ThreeVector(-77.9423*mm,   -15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 32);
  //new G4PVPlacement(zRot180, G4ThreeVector(-77.9423*mm,    15.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 33);
  //new G4PVPlacement(zRot240, G4ThreeVector(-77.9423*mm,    45.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 34);
  //new G4PVPlacement(zRot300, G4ThreeVector(-51.9615*mm,    60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 35);
  //new G4PVPlacement(      0, G4ThreeVector(-25.9808*mm,    75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 36);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,   120.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 37);
  //new G4PVPlacement(zRot120, G4ThreeVector( 25.9808*mm,   105.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 38);
  //new G4PVPlacement(zRot180, G4ThreeVector( 51.9615*mm,    90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 39);
  //new G4PVPlacement(zRot240, G4ThreeVector( 77.9423*mm,    75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 40);
  //new G4PVPlacement(zRot300, G4ThreeVector( 103.923*mm,    60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 41);
  //new G4PVPlacement(      0, G4ThreeVector( 103.923*mm,    30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 42);
  //new G4PVPlacement( zRot60, G4ThreeVector( 103.923*mm,     0.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 43);
  //new G4PVPlacement(zRot120, G4ThreeVector( 103.923*mm,   -30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 44);
  //new G4PVPlacement(zRot180, G4ThreeVector( 103.923*mm,   -60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 45);
  //new G4PVPlacement(zRot240, G4ThreeVector( 77.9423*mm,   -75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 46);
  //new G4PVPlacement(zRot300, G4ThreeVector( 51.9615*mm,   -90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 47);
  //new G4PVPlacement(      0, G4ThreeVector( 25.9808*mm,  -105.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 48);
  //new G4PVPlacement( zRot60, G4ThreeVector(  0.0000*mm,  -120.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 49);
  //new G4PVPlacement(zRot120, G4ThreeVector(-25.9808*mm,  -105.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 50);
  //new G4PVPlacement(zRot180, G4ThreeVector(-51.9615*mm,   -90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 51);
  //new G4PVPlacement(zRot240, G4ThreeVector(-77.9423*mm,   -75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 52);
  //new G4PVPlacement(zRot300, G4ThreeVector(-103.923*mm,   -60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 53);
  //new G4PVPlacement(      0, G4ThreeVector(-103.923*mm,   -30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 54);
  //new G4PVPlacement( zRot60, G4ThreeVector(-103.923*mm,     0.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 55);
  //new G4PVPlacement(zRot120, G4ThreeVector(-103.923*mm,    30.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 56);
  //new G4PVPlacement(zRot180, G4ThreeVector(-103.923*mm,    60.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 57);
  //new G4PVPlacement(zRot240, G4ThreeVector(-77.9423*mm,    75.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 58);
  //new G4PVPlacement(zRot300, G4ThreeVector(-51.9615*mm,    90.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 59);
  //new G4PVPlacement(      0, G4ThreeVector(-25.9808*mm,   105.0*mm,  0.0*mm), l_PDC, PDCName, l_Polarimeter, false, 60);
  //// place 30 SAS units
  //new G4PVPlacement(      0, G4ThreeVector(       0*mm,  154.33*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 0);
  //new G4PVPlacement(zRot300, G4ThreeVector( 32.7054*mm, 146.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 1);
  //new G4PVPlacement(zRot300, G4ThreeVector( 58.6861*mm, 131.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 2);
  //new G4PVPlacement(zRot300, G4ThreeVector( 84.6669*mm, 116.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 3);
  //new G4PVPlacement(zRot300, G4ThreeVector( 110.648*mm, 101.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 4);
  //new G4PVPlacement( zRot60, G4ThreeVector( 133.654*mm,  77.165*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 5);
  //new G4PVPlacement(      0, G4ThreeVector( 143.353*mm,    45.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 6);
  //new G4PVPlacement(      0, G4ThreeVector( 143.353*mm,    15.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 7);
  //new G4PVPlacement(      0, G4ThreeVector( 143.353*mm,   -15.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 8);
  //new G4PVPlacement(      0, G4ThreeVector( 143.353*mm,   -45.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 9);
  //new G4PVPlacement(zRot120, G4ThreeVector( 133.654*mm, -77.165*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 10);
  //new G4PVPlacement( zRot60, G4ThreeVector( 110.648*mm,-101.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 11);
  //new G4PVPlacement( zRot60, G4ThreeVector( 84.6669*mm,-116.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 12);
  //new G4PVPlacement( zRot60, G4ThreeVector( 58.6861*mm,-131.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 13);
  //new G4PVPlacement( zRot60, G4ThreeVector( 32.7054*mm,-146.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 14);
  //new G4PVPlacement(zRot180, G4ThreeVector(       0*mm, -154.33*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 15);
  //new G4PVPlacement(zRot120, G4ThreeVector(-32.7054*mm,-146.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 16);
  //new G4PVPlacement(zRot120, G4ThreeVector(-58.6861*mm,-131.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 17);
  //new G4PVPlacement(zRot120, G4ThreeVector(-84.6669*mm,-116.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 18);
  //new G4PVPlacement(zRot120, G4ThreeVector(-110.648*mm,-101.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 19);
  //new G4PVPlacement(zRot240, G4ThreeVector(-133.654*mm, -77.165*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 20);
  //new G4PVPlacement(zRot180, G4ThreeVector(-143.353*mm,   -45.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 21);
  //new G4PVPlacement(zRot180, G4ThreeVector(-143.353*mm,   -15.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 22);
  //new G4PVPlacement(zRot180, G4ThreeVector(-143.353*mm,    15.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 23);
  //new G4PVPlacement(zRot180, G4ThreeVector(-143.353*mm,    45.0*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 24);
  //new G4PVPlacement(zRot300, G4ThreeVector(-133.654*mm,  77.165*mm,159.5*mm), l_SAScornerUnit, SAScornerUnitName, l_Polarimeter, false, 25);
  //new G4PVPlacement(zRot240, G4ThreeVector(-110.648*mm, 101.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 26);
  //new G4PVPlacement(zRot240, G4ThreeVector(-84.6669*mm, 116.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 27);
  //new G4PVPlacement(zRot240, G4ThreeVector(-58.6861*mm, 131.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 28);
  //new G4PVPlacement(zRot240, G4ThreeVector(-32.7054*mm, 146.647*mm,159.5*mm),   l_SASedgeUnit,   SASedgeUnitName, l_Polarimeter, false, 29);


  //-------------------- Now define the sensitive detectors ----------------------------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

      TrackerSD* slowSD = new TrackerSD("slowSD");
      SDman->AddNewDetector(slowSD);
      l_Slow->SetSensitiveDetector(slowSD);

      TrackerSD* fastSD = new TrackerSD("fastSD");
      SDman->AddNewDetector(fastSD);
      l_Fast->SetSensitiveDetector(fastSD);

      TrackerSD* BGObottomSD = new TrackerSD("bottomBGOSD");
      SDman->AddNewDetector(BGObottomSD);
      l_BGObottom->SetSensitiveDetector(BGObottomSD);

      TrackerSD* SASSD = new TrackerSD("SASSD");
      SDman->AddNewDetector(SASSD);
      l_SASedge->SetSensitiveDetector(SASSD);
      l_SAScorner->SetSensitiveDetector(SASSD);
      l_SASbottom->SetSensitiveDetector(SASSD);

  //-------------------- Now define the visualization ----------------------------
  G4VisAttributes* colourWhite = new G4VisAttributes(G4Colour(1.,1.,1.));
  G4VisAttributes* colourBlue = new G4VisAttributes(G4Colour(0.,0.,1.));
  G4VisAttributes* colourLightBlue = new G4VisAttributes(G4Colour(0.6,0.6,1.));
  G4VisAttributes* colourLighterBlue = new G4VisAttributes(G4Colour(0.9,0.9,1.));
  G4VisAttributes* colourGrey = new G4VisAttributes(G4Colour(0.8,0.8,0.8));
  G4VisAttributes* colourDirtyYellow = new G4VisAttributes(G4Colour(1.0, 1.0, 0.6));
  G4VisAttributes* colourRed = new G4VisAttributes(G4Colour(1.0,0.4,0.4));
  colourWhite->SetForceSolid(true);
  colourBlue->SetForceSolid(true);
  colourLightBlue->SetForceSolid(true);
  colourLighterBlue->SetForceSolid(true);
  colourGrey->SetForceSolid(true);
  colourDirtyYellow->SetForceSolid(true);
  colourRed->SetForceSolid(true);

  l_Slow->SetVisAttributes(colourLighterBlue);
  l_PlasticCap->SetVisAttributes(colourWhite);
  l_Fast->SetVisAttributes(colourLightBlue);
  l_BGObottom->SetVisAttributes(colourRed);
  l_PM->SetVisAttributes(colourWhite);
  l_SASedge->SetVisAttributes(colourRed);
  l_SASedgeBone->SetVisAttributes(colourGrey);
  l_SAScorner->SetVisAttributes(colourRed);
  l_SAScornerBone->SetVisAttributes(colourGrey);
  l_SASbottom->SetVisAttributes(colourRed);

  l_World->SetVisAttributes(G4VisAttributes::Invisible);
  l_Pogo->SetVisAttributes(G4VisAttributes::Invisible);
  l_Polarimeter->SetVisAttributes(G4VisAttributes::Invisible);
  l_PDC->SetVisAttributes(G4VisAttributes::Invisible);
  l_HeatShrink->SetVisAttributes(G4VisAttributes::Invisible);
  l1_SnColl->SetVisAttributes(G4VisAttributes::Invisible);
  l2_SnColl->SetVisAttributes(G4VisAttributes::Invisible);
  l_PbColl->SetVisAttributes(G4VisAttributes::Invisible);
  l_SASedgeUnit->SetVisAttributes(G4VisAttributes::Invisible);
  l_SAScornerUnit->SetVisAttributes(G4VisAttributes::Invisible);

  return p_World;
}

void DetectorConstruction::SetPolarimeterRot(G4double phi)
{
  PolarimeterRot = phi;
  *zRot=*Rot0;
  zRot->rotateZ(PolarimeterRot);
  // rotate the mother volume Polarimeter to rotate all the detectors
  p_Polarimeter->SetRotation(zRot);

  // update the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4cout << "  Rotation of the polarimeter set to " << phi/deg << " deg" << G4endl;
}

void DetectorConstruction::SetElevation(G4double delta)
{
  Elevation = delta;
  *xRot=*Rot0;
  xRot->rotateX(Elevation);
  // rotate the mother volume Pogo to rotate all the instrument
  p_Pogo->SetRotation(xRot);

  // update the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4cout << "  Elevation set to " << delta/deg << " deg" << G4endl;
}

