// Include files
#include <cassert>
#include <algorithm>

// local
#include "GLMModel.hh"
#include "GLMPolynomial.hh"
#include "GLMBSpline.hh"
#include "GLMNSpline.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : GLMModel
//
// 2016-03-06 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

std::unique_ptr<GLMModel> GLMModel::CreateModel(GLMType type, int degree, const Distribution& pdf, Regression::LinkType link) {
  bool ignoreWeight = (link == Regression::LinkType::Mistag);
  if (type == GLMModel::GLMType::Polynomial) {
    Matrix basis = OrthonormalBasis(pdf,GLMPolynomial(degree),link,ignoreWeight);
    for (unsigned int n = 0; n < basis.size1(); n++) {
      for (unsigned int k = 0; k < basis.size2(); k++)
	basis(n,k) /= basis(n,n);
    }
    return std::make_unique<GLMPolynomial>(degree,basis);
  } else {
    // Create a quantiles function for Distribution!!!
    std::vector<double> nodes = pdf.GetQuantiles(degree+1);
    if (type == GLMModel::GLMType::BSpline) {
      return std::make_unique<GLMBSpline>(nodes);
    } else {
      assert(type == GLMModel::GLMType::NSpline);
      for (std::size_t k = 0; k < nodes.size(); k++) {
	nodes[k] = Regression::InvLink(nodes[k],link);
      }
      std::sort(nodes.begin(),nodes.end());
      Matrix basis = OrthonormalBasis(pdf,GLMNSpline(nodes),link,ignoreWeight);
      for (unsigned int n = 0; n < basis.size1(); n++) {
	for (unsigned int k = 0; k < basis.size2(); k++)
	  basis(n,k) /= basis(n,n);
      }
      return std::make_unique<GLMNSpline>(nodes,basis);
    }
  }
}

std::unique_ptr<GLMModel> GLMModel::CreateModel(GLMType type, int degree, const TaggingResult& tag, Regression::LinkType link) {
  bool ignoreWeight = (link == Regression::LinkType::Mistag);
  if (type == GLMModel::GLMType::Polynomial) {
    Matrix basis = OrthonormalBasis(tag,GLMPolynomial(degree),link,ignoreWeight);
    for (unsigned int n = 0; n < basis.size1(); n++) {
      for (unsigned int k = 0; k < basis.size2(); k++)
	basis(n,k) /= basis(n,n);
    }
    return std::make_unique<GLMPolynomial>(degree,basis);
  } else {
    std::vector<double> nodes = tag.EtaQuantiles(degree+1);
    if (type == GLMModel::GLMType::BSpline) {
      return std::make_unique<GLMBSpline>(nodes);
    } else {
      assert(type == GLMModel::GLMType::NSpline);
      for (std::size_t k = 0; k < nodes.size(); k++) {
	nodes[k] = Regression::InvLink(nodes[k],link);
      }
      std::sort(nodes.begin(),nodes.end());
      Matrix basis = OrthonormalBasis(tag,GLMNSpline(nodes),link,ignoreWeight);
      for (unsigned int n = 0; n < basis.size1(); n++) {
	 for (unsigned int k = 0; k < basis.size2(); k++)
	  basis(n,k) /= basis(n,n);
      }
      return std::make_unique<GLMNSpline>(nodes,basis);
    }
  }
}

Matrix Espresso::OrthonormalBasis(const Distribution& pdf, const GLMModel& model, Regression::LinkType link, bool ignoreWeight) {

  // FIND FIRST 2N MOMENTS
  unsigned int length = model.NumParams();
  Matrix covariances(length,length);
  for (unsigned int k = 0; k < length; k++) {
    for (unsigned int l = 0; l < length; l++) {
      Function f = [&link,&model,&k,&l,&ignoreWeight] (double eta) -> double {
	double denom = 1.0;
	if (!ignoreWeight) {
	  double dinvlink = Regression::DInvLink(eta,link);
	  denom = eta*(1-eta)*dinvlink*dinvlink;
	}
	Vector bvals = (model.PreProcessWithLink())
	? model.GetBasis(Regression::InvLink(eta,link))
	: model.GetBasis(eta);
	return bvals(k)*bvals(l)/denom;
      };
      covariances(k,l) = pdf.Expectation(f);
    }
  }

  return GramSchmidt(covariances);

}

Matrix Espresso::OrthonormalBasis(const TaggingResult& res, const GLMModel& model, Regression::LinkType link, bool ignoreWeight) {
  // Loop over table to get moments
  unsigned int length = model.NumParams();
  double sumw = 0.0;
  Matrix covariances(length,length);
  const TaggingResult::TagTable& table = res.GetTagTable();
  for (TaggingResult::TagInfo info : table) {
    if (info.predFlavour == Flavour::Unknown) continue;
    double eta = info.eta;
    double w = info.W;
    sumw += w;
    double denom = 1.0;
    if (!ignoreWeight) {
      double dinvlink = Regression::DInvLink(eta,link);
      denom = eta*(1-eta)*dinvlink*dinvlink;
    }
    Vector bvals = (model.PreProcessWithLink())
      ? model.GetBasis(Regression::InvLink(eta,link))
      : model.GetBasis(eta);
    for (unsigned int k = 0; k < length; k++) {
      for (unsigned int l = 0; l < length; l++) {
	covariances(k,l) += w*bvals(k)*bvals(l)/denom;
      }
    }
  }
  covariances /= sumw;

  return GramSchmidt(covariances);
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMModel)
