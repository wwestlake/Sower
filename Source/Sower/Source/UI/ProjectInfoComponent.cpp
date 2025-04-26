#include "ProjectInfoComponent.h"

ProjectInfoComponent::ProjectInfoComponent()
{
    addAndMakeVisible(projectNameField);
    addAndMakeVisible(authorField);
    addAndMakeVisible(copyrightField);
    addAndMakeVisible(descriptionField);
    addAndMakeVisible(fileSelector);
}

void ProjectInfoComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void ProjectInfoComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto fieldHeight = 50;
    auto selectorHeight = 500;

    projectNameField.setBounds(area.removeFromTop(fieldHeight).reduced(0, 4));
    authorField.setBounds(area.removeFromTop(fieldHeight).reduced(0, 4));
    copyrightField.setBounds(area.removeFromTop(fieldHeight).reduced(0, 4));
    descriptionField.setBounds(area.removeFromTop(fieldHeight).reduced(0, 4));
    fileSelector.setBounds(area.removeFromTop(selectorHeight).reduced(0, 4));
}

juce::var ProjectInfoComponent::getJson() const
{
    juce::DynamicObject::Ptr json = new juce::DynamicObject();

    json->setProperty("projectName", projectNameField.getText());
    json->setProperty("author", authorField.getText());
    json->setProperty("copyright", copyrightField.getText());
    json->setProperty("description", descriptionField.getText());

    return json.get();
}

void ProjectInfoComponent::setFromJson(const juce::var& json)
{
    if (auto* obj = json.getDynamicObject())
    {
        projectNameField.setText(obj->getProperty("projectName").toString());
        authorField.setText(obj->getProperty("author").toString());
        copyrightField.setText(obj->getProperty("copyright").toString());
        descriptionField.setText(obj->getProperty("description").toString());
    }
}
