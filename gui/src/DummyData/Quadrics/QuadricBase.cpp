// 
// //---------------------------------------------------------------------------
// void CGQuadric::createUVSphere(int slices, int stacks)
// {
// 	float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
// 	float slr = (2 * (float)M_PI) / (float)slices;
// 	float str = (float)(M_PI) / (float)stacks;
// 	for (int iSt = 0; iSt < stacks; ++iSt) {
// 		float rho = -(float)M_PI / 2.0f + (float)M_PI*(float(iSt) / float(stacks));
// 		for (int iSl = 0; iSl < slices; ++iSl) {
// 			float phi = 2.0f*(float)M_PI*float(iSl) / float(slices);
// 			x0 = cos(rho)*cos(phi);
// 			y0 = cos(rho)*sin(phi);
// 			z0 = sin(rho);
// 			x1 = cos(rho)*cos(phi + slr);
// 			y1 = cos(rho)*sin(phi + slr);
// 			z1 = sin(rho);
// 			x2 = cos(rho + str)*cos(phi + slr);
// 			y2 = cos(rho + str)*sin(phi + slr);
// 			z2 = sin(rho + str);
// 			x3 = cos(rho + str)*cos(phi);
// 			y3 = cos(rho + str)*sin(phi);
// 			z3 = sin(rho + str);
// 			if (iSt == 0)
// 				m_addTriangle(0, 0, -1, 0, 0, -1,
// 					x2, y2, z2, x2, y2, z2,
// 					x3, y3, z3, x3, y3, z3);
// 			else if (iSt == stacks - 1)
// 				m_addTriangle(x0, y0, z0, x0, y0, z0,
// 					x1, y1, z1, x1, y1, z1,
// 					0, 0, 1, 0, 0, 1);
// 			else
// 				m_addQuad(x0, y0, z0, x0, y0, z0,
// 					x1, y1, z1, x1, y1, z1,
// 					x2, y2, z2, x2, y2, z2,
// 					x3, y3, z3, x3, y3, z3);
// 		}
// 	}
// }
// //---------------------------------------------------------------------------
// void CGQuadric::m_subdivideTriangle(int subdiv, float r, float g, float b,
// 	float x0, float y0, float z0,
// 	float x1, float y1, float z1,
// 	float x2, float y2, float z2)
// {
// 	if (subdiv > 0) {
// 		//subdivide further
// 		--subdiv;
// 		float x3, y3, z3, x4, y4, z4, x5, y5, z5;
// 		//1. calculate new positions
// 		x3 = 0.5f*x0 + 0.5f*x1;    //            v2                //
// 		y3 = 0.5f*y0 + 0.5f*y1;    //           /  \               //
// 		z3 = 0.5f*z0 + 0.5f*z1;    //          /    \              //
// 								 //         /      \             //
// 		x4 = 0.5f*x1 + 0.5f*x2;    //        /        \            //
// 		y4 = 0.5f*y1 + 0.5f*y2;    //       v5---------v4          //
// 		z4 = 0.5f*z1 + 0.5f*z2;    //      / \        / \          //
// 								 //     /   \      /   \         //
// 		x5 = 0.5f*x2 + 0.5f*x0;    //    /     \    /     \        //
// 		y5 = 0.5f*y2 + 0.5f*y0;    //   /       \  /       \       //
// 		z5 = 0.5f*z2 + 0.5f*z0;    // v0---------v3---------v1     //
// 		//2. normalize them
// 		float l;
// 		l = sqrt(x3*x3 + y3*y3 + z3*z3);
// 		x3 /= l; y3 /= l; z3 /= l;
// 		l = sqrt(x4*x4 + y4*y4 + z4*z4);
// 		x4 /= l; y4 /= l; z4 /= l;
// 		l = sqrt(x5*x5 + y5*y5 + z5*z5);
// 		x5 /= l; y5 /= l; z5 /= l;
// 		m_subdivideTriangle(subdiv, r, g, b,
// 			x0, y0, z0,
// 			x3, y3, z3,
// 			x5, y5, z5);
// 		m_subdivideTriangle(subdiv, r, g, b,
// 			x3, y3, z3,
// 			x1, y1, z1,
// 			x4, y4, z4);
// 		m_subdivideTriangle(subdiv, r, g, b,
// 			x5, y5, z5,
// 			x3, y3, z3,
// 			x4, y4, z4);
// 		m_subdivideTriangle(subdiv, r, g, b,
// 			x2, y2, z2,
// 			x5, y5, z5,
// 			x4, y4, z4);
// 	}
// 	else {
// 		m_addTriangle(x0, y0, z0, x0, y0, z0,
// 			x1, y1, z1, x1, y1, z1,
// 			x2, y2, z2, x2, y2, z2);
// 	}
// }
// void CGQuadric::createIcoSphere(int subdiv)
// {
// 	// create 4 initial triangles
// 	//upper part
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		1, 0, 0,
// 		0, 0, -1,
// 		0, 1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		0, 0, -1,
// 		-1, 0, 0,
// 		0, 1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		-1, 0, 0,
// 		0, 0, 1,
// 		0, 1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		0, 0, 1,
// 		1, 0, 0,
// 		0, 1, 0);
// 	//lower part
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		0, 0, -1,
// 		1, 0, 0,
// 		0, -1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		-1, 0, 0,
// 		0, 0, -1,
// 		0, -1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		0, 0, 1,
// 		-1, 0, 0,
// 		0, -1, 0);
// 	m_subdivideTriangle(subdiv, 1, 1, 1,
// 		1, 0, 0,
// 		0, 0, 1,
// 		0, -1, 0);
// }
// //---------------------------------------------------------------------------
// void CGQuadric::createCylinder(int slices, int stacks)
// {
// 	// create (stacks-1) rings
// 	for (int iSt = 0; iSt < stacks; iSt++) {
// 		float zb = float(iSt) / float(stacks);
// 		float zt = float(iSt + 1) / float(stacks);
// 		// with (slices-1) elements
// 		for (int iSl = 0; iSl < slices; iSl++) {
// 			float sliceRatioL = float(iSl) / float(slices);
// 			float sliceRatioR = float(iSl + 1) / float(slices);
// 			float cl = cosf(sliceRatioL*(float)M_PI*2.0f), sl = sinf(sliceRatioL*(float)M_PI*2.0f),
// 				cr = cosf(sliceRatioR*(float)M_PI*2.0f), sr = sinf(sliceRatioR*(float)M_PI*2.0f);
// 			m_addQuad(cl, sl, zb, cl, sl, 0,
// 				cr, sr, zb, cr, sr, 0,
// 				cr, sr, zt, cr, sr, 0,
// 				cl, sl, zt, cl, sl, 0);
// 		}
// 	}
// }
// //---------------------------------------------------------------------------
// void CGQuadric::createDisk(int slices, int loops)
// {
// 	// create (loops-1) rings
// 	for (int iL = 0; iL < loops; iL++) {
// 		float ro = (1.0f - float(iL) / float(loops)); // outer radius
// 		float ri = (1.0f - float(iL + 1) / float(loops)); // inner radius
// 		// with (slices-1) elements
// 		for (int iSl = 0; iSl < slices; iSl++) {
// 			float sliceRatioL = float(iSl) / float(slices);
// 			float sliceRatioR = float(iSl + 1) / float(slices);
// 			float cl = cosf(sliceRatioL*(float)M_PI*2.0f), sl = sinf(sliceRatioL*(float)M_PI*2.0f),
// 				cr = cosf(sliceRatioR*(float)M_PI*2.0f), sr = sinf(sliceRatioR*(float)M_PI*2.0f);
// 			if (iL == loops - 1)
// 				m_addTriangle(cl*ro, sl*ro, 0, 0, 0, 1,
// 					cr*ro, sr*ro, 0, 0, 0, 1,
// 					0, 0, 0, 0, 0, 1);
// 			else
// 				m_addQuad(cl*ro, sl*ro, 0, 0, 0, 1,
// 					cr*ro, sr*ro, 0, 0, 0, 1,
// 					cr*ri, sr*ri, 0, 0, 0, 1,
// 					cl*ri, sl*ri, 0, 0, 0, 1);
// 		}
// 	}
// }
// //---------------------------------------------------------------------------
// void CGQuadric::createCone(int slices, int stacks)
// {
// 	createCone(1.0f, slices, stacks);
// }
// //---------------------------------------------------------------------------
// void CGQuadric::createCone(float maxHeight, int slices, int stacks)
// {
// 	// this is a small normal trick:
// 	float n[3] = { 1,0,1 };
// 	float len = sqrt(n[0] * n[0] + n[2] * n[2]);
// 	n[0] /= len; n[2] /= len;
// 	// create (loops-1) rings
// 	for (float iSt = 0; iSt < maxHeight; iSt += (maxHeight / (float)stacks)) {
// 		float br = (1.0f - iSt); // bottom radius
// 		float tr = (1.0f - iSt - (maxHeight / (float)stacks)); // top radius
// 		float bz = iSt;
// 		float tz = iSt + (maxHeight / (float)stacks);
// 		// with (slices-1) elements
// 		for (int iSl = 0; iSl < slices; iSl++) {
// 			float sliceRatioL = float(iSl) / float(slices);
// 			float sliceRatioR = float(iSl + 1) / float(slices);
// 			float cl = cosf(sliceRatioL*(float)M_PI*2.0f), sl = sinf(sliceRatioL*(float)M_PI*2.0f),
// 				cr = cosf(sliceRatioR*(float)M_PI*2.0f), sr = sinf(sliceRatioR*(float)M_PI*2.0f);
// 			float nlx = cl*n[0], nly = sl*n[0], nlz = n[2],
// 				nrx = cr*n[0], nry = sr*n[0], nrz = n[2];
// 			if (iSt < (1.0f - (maxHeight / (float)stacks)))
// 				m_addQuad(cl*br, sl*br, bz, nlx, nly, nlz,
// 					cr*br, sr*br, bz, nrx, nry, nrz,
// 					cr*tr, sr*tr, tz, nrx, nry, nrz,
// 					cl*tr, sl*tr, tz, nlx, nly, nlz);
// 			else
// 				m_addTriangle(cl*br, sl*br, bz, nlx, nly, nlz,
// 					cr*br, sr*br, bz, nrx, nry, nrz,
// 					0, 0, tz, nrx, nry, nrz);
// 		}
// 	}
// }
// //---------------------------------------------------------------------------
