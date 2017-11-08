/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the abstract GLMModel class.
 */

#ifndef ESPRESSO_GLMMODEL_HH
#define ESPRESSO_GLMMODEL_HH 1

#include <boost/serialization/export.hpp>

#include "TaggingResult.hh"

namespace Espresso {

  /**
   * @class GLMModel
   * @brief This is an abstract interface for a generalized linear model (GLM).
   * @details A GLM is a function g<sub>0</sub> + &theta;<sub>i</sub> b(&eta;)<sup>i</sup>
   * where b(&eta;)<sup>i</sup> are a set of pre-determined basis functions
   * and the &theta;<sub>i</sub> are free parameters to be determined in a regression procedure.
   * The main option for a GLM is the type of functions b(&eta;)<sup>i</sup>
   * (usually polynomials or splines). Since the GLM is used in combination of a link function g
   * that transforms its linear output, e.g. a sigmoid function in the logit link case, there
   * are two options about how to deal with this. One is whether to specify an offset value
   * g<sub>0</sub> = g<sup>-1</sup>(&eta;). The other is whether the b should be a function of &eta;
   * or g<sup>-1</sup>(&eta;). Each of these can have advantages in certain cases.
   */
  class GLMModel {
  public:

    /// Virtual destructor
    virtual ~GLMModel() {};

    /**
     * @brief Whether to use &eta; as approximation to &omega;
     * @details The uncalibrated mistag &eta; should be reasonably close to the calibrated
     * value &omega;. So, it usually makes sense to model the GLM as
     * g(&omega;) = g(&eta;) + &theta;<sub>i</sub> b(&eta;)<sup>i</sup>
     * where g is the link function being used. With this choice, a calibration to an
     * already perfectly calibrated tagger would have &theta;<sub>i</sub> = 0.
     */
    virtual bool SubtractEta() const = 0;

    /**
     * @brief Whether to apply basis function to &eta; or g(&eta;)
     * @details The uncalibrated mistag &eta; should be reasonably close to the calibrated
     * value &omega;. So, if the functions b are themselves interpretable
     * (for example, polynomials or polynomial-like natural splines),
     * the interpretability of the GLM is improved by modelling it as
     * g(&omega;) = g<sub>0</sub> &theta;<sub>i</sub> b(g(&eta;))<sup>i</sup>
     * where g is the link function being used. With this transformation,
     * in a linear calibration &theta;<sub>0</sub> and &theta;<sub>1</sub>
     * are still a mean and a slope in the transformed space g([0,1]), e.g.
     * g(&omega;) = g<sub>0</sub> + &theta;<sub>0</sub> + &theta;<sub>1</sub>g(&eta;)
     */
    virtual bool PreProcessWithLink() const = 0;

    /// Returns the number of elements in the GLM basis
    virtual unsigned int NumParams() const = 0;

    /// Returns the vector of basis elements at &eta;
    virtual Vector GetBasis(double eta) const = 0;

    /// Print to an std::ostream
    virtual void print(std::ostream& os) const = 0;

    /// Uses virtual function GLMModel::print to overload GLMModel::operator<<
    friend std::ostream& operator<< (std::ostream& os, const GLMModel& glm) { glm.print(os); return os; };

    /// Clones the model, returning a smart pointer
    std::unique_ptr<GLMModel> clone() const { return std::unique_ptr<GLMModel>(doClone()); }

    /**
     * This enumerates the classes of GLMs
     */
    enum class GLMType {
      Polynomial, ///< using GLMPolynomial
      BSpline, ///< GLMBSpline
      NSpline ///< GLMNSpline
    };

    /**
     * @brief Named constructor to create a GLMModel optimized for an analytic mistag distribution
     * @param[in] type Desired GLM type
     * @param[in] degree Desired degree (consult type for specific meaning in each case)
     * @param[in] tag Analytic mistag distribution to optimize to
     * @param[in] link Regression link type to use
     * @return A smart pointer containing the created model
     */
    static std::unique_ptr<GLMModel> CreateModel(GLMType type, int degree, const Distribution& tag, Regression::LinkType link);

    /**
     * @brief Named constructor to create a GLMModel optimized for a real mistag distribution
     * @param[in] type Desired GLM type
     * @param[in] degree Desired degree (consult type for specific meaning in each case)
     * @param[in] tag Tagging result with real mistag distribution to optimize to
     * @param[in] link Regression link type to use
     * @return A smart pointer containing the created model
     */
    static std::unique_ptr<GLMModel> CreateModel(GLMType type, int degree, const TaggingResult& tag, Regression::LinkType link);

  private:

    virtual GLMModel* doClone() const = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {}
  };

  /**
   * @brief Finds the best basis for calibrating this tag set
   * @details This is basically a shortcut to Espresso::GramSchmidt in Statistics.hh
   * that automatically uses the dilution distribution observed in this tagging result.
   * It computes the transformation that makes the basis orthogonal.
   * These orthogonal basis functions satisfy
   * \f[ \sum_i P_j(x_i) P_k(x_i) w(x_i) \propto \delta_{jk} \f]
   * where w(x) is a weight function dpending on the regression link type.
   * @param[in] res TaggingResult object
   * @param[in] model GLMModel to orthogonalize
   * @param[in] link Type of regression link used to process &eta;
   */
  Matrix OrthonormalBasis(const TaggingResult& res, const GLMModel& model, Regression::LinkType link, bool ignoreWeight = false);

  /**
   * @brief Finds the best basis for calibrating a toy tagger with this mistag distribution
   * @details This is basically a shortcut to Espresso::GramSchmidt in Statistics.hh
   * that uses the provided analytic mistag distribution.
   * It computes the transformation that makes the basis orthogonal.
   * These orthogonal basis functions satisfy
   * \f[ \int_{x_\mathrm{min}}^{x_\mathrm{max}} P_j(x) P_k(x) w(x) \mathrm{pdf}(x) \, dx \propto \delta_{jk} \f]
   * where w(x) is a weight function dpending on the regression link type.
   * @param[in] pdf Analytic mistag distribution
   * @param[in] model GLMModel to orthogonalize
   * @param[in] link Type of regression link used to process &eta;
   */
  Matrix OrthonormalBasis(const Distribution& pdf, const GLMModel& model, Regression::LinkType link, bool ignoreWeight = false);


}

BOOST_CLASS_EXPORT_KEY(Espresso::GLMModel)

#endif
