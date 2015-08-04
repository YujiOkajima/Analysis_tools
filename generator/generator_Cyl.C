void generator_Cyl(double zmax, double r2max, double energy, string detector, int particle, int neutrino, double mass){
  //zmax: half of detector height
  //r2max: detector radius
  //energy: kinetic energy
  //detector: detector name
  //particle: particle ID of target particle
  //neutrino: neutrino which is interacted with target particle
  //mass mass of target particle

  TRandom random(0);

  char filename[100];
  double zmax;
  double energy;
  double r2max;
  double vertex[3];
  double dir[3];
  double nev;
  double phi;
  r2max=r2max-200;

    r2max*=r2max;
    sprintf(filename,"eventlist_%s_particle%d_%dMeV.txt",detector.c_str(),particle,(int)energy);
    ofstream ofs(filename);
    for(nev=0; nev<10000; nev++)
      {
	vertex[1]=sqrt(r2max*random.Rndm());
	vertex[2]=6.283185307*random.Rndm();
	vertex[0]=vertex[1]*cos(vertex[2]);
	vertex[1]*=sin(vertex[2]);
	vertex[2]=(zmax-200)*(2*random.Rndm()-1);
	phi=6.283185307*random.Rndm();
	dir[2]=2*random.Rndm()-1;
	dir[1]=sqrt(1-dir[2]*dir[2]);
	dir[0]=dir[1]*cos(phi);
	dir[1]*=sin(phi);
	
	double momentum = sqrt((energy+mass)*(energy+mass)-mass*mass);
	double totalenergy=(mass+momentum+sqrt(mass*mass+momentum*momentum))/2;
	
	ofs << "$begin" << std::endl;
	ofs << "$neut 3" << std::endl;
	ofs << "$vertex " << vertex[0] << " " << vertex[1] << " " << vertex[2] << " dummy" << std::endl;
	ofs << "$track " << particle << " " << mass << " 0 0 0 -1" << std::endl;
	ofs << "$track " << neutrino << " " << totalenergy-mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "-1" << std::endl;
	ofs << "$info event " << nev+1 << std::endl;
	ofs << "$track " << particle << " " << energy+mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "-2" << std::endl;
	ofs << "$track " << neutrino << " " << totalenergy-sqrt(momentum*momentum+mass*mass) << " " << -dir[0] << " " << -dir[1] << " " << -dir[2] << " " << "-2" << std::endl;
	ofs << "$track " << particle << " " << energy+mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "0" << std::endl;
	ofs << "$track " << neutrino << " " << totalenergy-sqrt(momentum*momentum+mass*mass) << " " << -dir[0] << " " << -dir[1] << " " << -dir[2] << " " << "0" << std::endl;
	ofs << "$end" << std::endl;
      }
    ofs << "$ stop" << std::endl;
    ofs.close();
}
